#include "TcpConnection.h"

#include <errno.h>
#include <netinet/tcp.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <functional>

#include "Channel.h"
#include "EventLoop.h"
#include "Logging.h"
#include "Socket.h"

static EventLoop *checkLoopNotNull(EventLoop *loop) {
  if (loop == nullptr) {
    LOG_FATAL << "mainLoop is null!";
  }
  return loop;
}

TcpConnection::TcpConnection(EventLoop *loop, const std::string &name,
                             int sockfd, const InetAddress &localAddr,
                             const InetAddress &peerAddr)
    : loop_(checkLoopNotNull(loop)),
      name_(name),
      state_(kConnecting),
      reading_(true),
      socket_(new Socket(sockfd)),
      channel_(new Channel(loop_, sockfd)),
      localAddr_(localAddr),
      peerAddr_(peerAddr),
      highWaterMark_(64 * 1024 * 1024) {
  channel_->setReadCallBack(
      std::bind(&TcpConnection::handleRead, this, std::placeholders::_1));
  channel_->setWriteCallBack(std::bind(&TcpConnection::handleWrite, this));
  channel_->setCloseCallBack(std::bind(&TcpConnection::handleClose, this));
  channel_->setErrorCallBack(std::bind(&TcpConnection::handleError, this));

  LOG_INFO << "TcpConnection ctor[ " << name_.c_str() << " ] at fd" << sockfd;
  // 设置tcp长连接
  socket_->setKeepAlive(true);
}

TcpConnection::~TcpConnection() {
  LOG_INFO << "TcpConnection dtor[ " << name_.c_str() << " ] at fd"
           << channel_->fd() << "state_ = " << static_cast<int>(state_);
}

void TcpConnection::send(const std::string &buf) {
  if (state_ == kConnected) {
    if (loop_->isInLoopThread()) {
      sendInLoop(buf.c_str(), buf.size());
    } else {
      void (TcpConnection::*fp)(const void *data, size_t len) =
          &TcpConnection::sendInLoop;
      loop_->runInLoop(std::bind(fp, this, buf.c_str(), buf.size()));
    }
  }
}

void TcpConnection::send(Buffer *buf) {
  if (state_ == kConnected) {
    if (loop_->isInLoopThread()) {
      sendInLoop(buf->peek(), buf->readableBytes());
      buf->retrieveAll();
    } else {
      // sendInLoop有多重重载，需要使用函数指针确定
      void (TcpConnection::*fp)(const std::string &message) =
          &TcpConnection::sendInLoop;
      loop_->runInLoop(std::bind(fp, this, buf->retrieveAllAsString()));
    }
  }
}

void TcpConnection::shutdown() {
  if (state_ == kConnected) {
    setState(kDisconnecting);
    loop_->runInLoop(std::bind(&TcpConnection::shutdownInLoop, this));
  }
}

void TcpConnection::connectEstablished() {
  setState(kConnected);  // 建立连接，设置一开始状态为连接态
  /**
   * TODO:tie
   * channel_->tie(shared_from_this());
   * tie相当于在底层有一个强引用指针记录着，防止析构
   * 为了防止TcpConnection这个资源被误删掉，而这个时候还有许多事件要处理
   * channel->tie
   * 会进行一次判断，是否将弱引用指针变成强引用，变成得话就防止了计数为0而被析构得可能
   */
  channel_->tie(shared_from_this());
  // 向poller注册channel的EPOLLIN读事件
  channel_->enableReadEvent();

  // 新连接建立 执行回调
  connectionCallback_(shared_from_this());
}

void TcpConnection::connectDestroyed() {
  if (state_ == kConnected) {
    setState(kDisconnected);
    channel_->disAllEvent();  // 把channel的所有感兴趣的事件从poller中删除掉
    connectionCallback_(shared_from_this());
  }
  channel_->remove();  // 把channel从poller中删除掉
}

void TcpConnection::handleRead(Timestamp receiveTime) {
  int savedErrno = 0;
  // TcpConnection会从socket读取数据，然后写入inpuBuffer
  ssize_t n = inputBuffer_.readFd(channel_->fd(), &savedErrno);
  if (n > 0) {
    // 已建立连接的用户，有可读事件发生，调用用户传入的回调操作
    messageCallback_(shared_from_this(), &inputBuffer_, receiveTime);
  } else if (n == 0) {
    // 没有数据，说明客户端关闭连接
    handleClose();
  } else {
    // 出错情况
    errno = savedErrno;
    LOG_ERROR << "TcpConnection::handleRead() failed";
    handleError();
  }
}

void TcpConnection::handleWrite() {
  if (channel_->isWriting()) {
    int saveErrno = 0;
    ssize_t n = outputBuffer_.writeFd(channel_->fd(), &saveErrno);
    // 正确读取数据
    if (n > 0) {
      outputBuffer_.retrieve(n);
      // 说明buffer可读数据都被TcpConnection读取完毕并写入给了客户端
      // 此时就可以关闭连接，否则还需继续提醒写事件
      if (outputBuffer_.readableBytes() == 0) {
        channel_->disableWriteEvent();
        // 调用用户自定义的写完数据处理函数
        if (writeCompleteCallback_) {
          // 唤醒loop_对应得thread线程，执行写完成事件回调
          loop_->queueInLoop(
              std::bind(writeCompleteCallback_, shared_from_this()));
        }
        if (state_ == kDisconnecting) {
          shutdownInLoop();
        }
      }
    } else {
      LOG_ERROR << "TcpConnection::handleWrite() failed";
    }
  } else {  // state_不为写状态
    LOG_ERROR << "TcpConnection fd=" << channel_->fd()
              << " is down, no more writing";
  }
}

void TcpConnection::handleClose() {
  setState(kDisconnected);  // 设置状态为关闭连接状态
  channel_->disAllEvent();  // 注销Channel所有感兴趣事件

  TcpConnectionPtr connPtr(shared_from_this());
  connectionCallback_(connPtr);
  closeCallback_(connPtr);  // 关闭连接的回调
}

void TcpConnection::handleError() {
  int optval;
  socklen_t optlen = sizeof(optval);
  int err = 0;
  if (::getsockopt(channel_->fd(), SOL_SOCKET, SO_ERROR, &optval, &optlen)) {
    err = errno;
  } else {
    err = optval;
  }
  LOG_ERROR << "cpConnection::handleError name:" << name_.c_str()
            << " - SO_ERROR:" << err;
}

void TcpConnection::sendInLoop(const std::string &message) {
  sendInLoop(message.data(), message.size());
}

void TcpConnection::sendInLoop(const void *message, size_t len) {
  ssize_t nwrote = 0;
  size_t remainning = len;
  bool faultError = false;

  if (state_ == kDisconnected) {
    LOG_ERROR << "state_ == kDisconnected, give up";
    return;
  }

  if (!channel_->isWriting() && outputBuffer_.readableBytes() == 0) {
    nwrote = ::write(channel_->fd(), message, len);
    if (nwrote >= 0) {
      remainning = len - nwrote;
      if (remainning == 0 && writeCompleteCallback_) {
        // 如果一次性写完了 只需要处理写完的回调就行了
        loop_->queueInLoop(
            std::bind(writeCompleteCallback_, shared_from_this()));
      }
    }
  } else {
    nwrote = 0;
    // 排除是因为没有可写数据造成的问题
    if (errno != EWOULDBLOCK) {
      LOG_ERROR << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__
                << "failed";
      // 如果是因为对端关闭了连接
      // 但是仍然尝试写入导致的错误那就还需要将默认错误标记设置一下
      // 这样做的目的是方便之后执行处理错误的回调
      if (errno == EPIPE || errno == ECONNRESET) {
        faultError = true;
      }
    }
  }
  // 未发生重大错误并且仍有未写完的数据
  if (!faultError && remainning > 0) {
    size_t oldlen = outputBuffer_.readableBytes();
    if (oldlen + remainning >= highWaterMark_ && oldlen < highWaterMark_ &&
        highWaterMarkCallback_) {
      loop_->queueInLoop(std::bind(highWaterMarkCallback_, shared_from_this(),
                                   oldlen + remainning));
    }
    // 将还未发送的数据打到输出缓冲区中
    outputBuffer_.append((char *)message + nwrote, remainning);
    if (!channel_->isWriting()) {
      // 注册channel的写事件
      // 这样poller给channel通知epollout
      channel_->enableWriteEvent();
    }
  }
}

void TcpConnection::shutdownInLoop() {
  // 说明当前outputBuffer_的数据全部向外发送完成
  if (!channel_->isWriting()) {
    socket_->shutdownWrite();
  }
}
