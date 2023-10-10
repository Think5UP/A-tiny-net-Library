#include "Acceptor.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <functional>

#include "InetAddress.h"
#include "Logging.h"

static int createNonblocking() {
  int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC,
                        IPPROTO_TCP);
  if (sockfd < 0) {
    LOG_FATAL << "listen socket create failed: " << errno;
  }
  return sockfd;
}

Acceptor::Acceptor(EventLoop *loop, const InetAddress &listenAddr,
                   bool reusePort)
    : loop_(loop),
      acceptSocket_(createNonblocking()),
      acceptChannel_(loop, acceptSocket_.fd()),
      listenning_(false) {
  LOG_DEBUG << "Acceptor create nonblocking socket, [fd = "
            << acceptChannel_.fd() << "]";
  acceptSocket_.setReuseAddr(reusePort);
  acceptSocket_.setReusePort(true);
  acceptSocket_.bindAddress(listenAddr);

  // 在TCPServer的start函数启动之后会调用listen 这里就需要去处理新连接的回调
  // 因此需要向acceptChannel_的channel注册一个回调
  acceptChannel_.setReadCallBack(std::bind(&Acceptor::handleRead, this));
}

Acceptor::~Acceptor() {
  // 将感兴趣的事件从channel以及注册的poller中删除
  acceptChannel_.disAllEvent();
  // 调用EventLoop->removeChannel => Poller->removeChannel
  // 把Poller的ChannelMap对应的部分删除
  acceptChannel_.remove();
}

void Acceptor::listen() {
  listenning_ = true;
  // 开始监听
  acceptSocket_.listen();
  // 将监听连接的描述符的读事件注册到poller上
  acceptChannel_.enableReadEvent();
}

void Acceptor::handleRead() {
  InetAddress peerAddr;
  int connfd = acceptSocket_.accept(&peerAddr);
  if (connfd >= 0) {
    // 确实到来了新的连接
    // 并且新连接的回调已经注册 处理回调
    if (newConnectionCallback_) {
      newConnectionCallback_(connfd, peerAddr);
    } else {
      LOG_DEBUG << "no newConnectionCallback_ function";
      ::close(connfd);
    }
  } else {
    LOG_ERROR << "accept faild";
    // 这里代表当前进程已经打到了最大限制的文件描述符限制
    // 考虑分布式或者改变系统进程最大的文件描述符数量
    if (errno == EMFILE) {
      LOG_ERROR << "sockfd reached limit";
    }
  }
}
