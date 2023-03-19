//
// Created by root on 3/6/23.
//
#include <functional>

#include "Socket.h"
#include "Channel.h"
#include "EventLoop.h"
#include "TCPConnection.h"
#include "../Base/Logger.h"

static net_lib::EventLoop* checkNotNull(net_lib::EventLoop* loop){
    if(loop == nullptr){
        LOG_FATAL("%s:%s:%d subloop is null",__FILE__, __FUNCTION__, __LINE__);
    }
    return loop;
}

namespace net_lib {
    TCPConnection::TCPConnection(EventLoop *loop, const std::string &name,
                                 int sockfd, const InetaAddress &localAddr,
                                 const InetaAddress &peerAddr)
            : loop_(checkNotNull(loop)),
              name_(name),
              state_(kConnecting),
              reading_(true),
              localAddr_(localAddr),
              peerAddr_(peerAddr),
              socket_(new Socket(sockfd)),
              channel_(new Channel(loop_, sockfd)),
              highWaterMark_(64 * 1024 * 1024) {
        channel_->setReadEventCallBack(
                std::bind(&TCPConnection::handleRead, this, std::placeholders::_1)
        );
        channel_->setWriteEventCallBack(
                std::bind(&TCPConnection::handelWrite, this)
        );
        channel_->setCloseEventCallBack(
                std::bind(&TCPConnection::handleClose, this)
        );
        channel_->setErrorEventCallBack(
                std::bind(&TCPConnection::handleError, this)
        );
        LOG_INFO("TCPConnection ctor[%s] at fd=%d\n", name_.c_str(), sockfd);
        socket_->setKeepAlive(true);
    }

    TCPConnection::~TCPConnection() {
        LOG_INFO("TCPConnection dtor[%s] at fd=%d state=%s\n", name_.c_str(), channel_->fd(), StateToString().c_str());
    }

    const std::string TCPConnection::StateToString() {
        switch (state_) {
#define XX(name)                    \
        case StateE::name:           \
            return #name;           \
            break;
            XX(kDisConnected);
            XX(kConnecting);
            XX(kConnected);
            XX(kDisConnecting);
#undef XX
            default:
                return "ERROR";
        }
        return "ERROR";
    }

    void TCPConnection::send(Buffer *buf) {
        if(state_ == kConnected){
            if(loop_->isInLoopThread()){
                sendInLoop(buf->peek(),buf->readableBytes());
                buf->retrieveAll();
            } else {
                void(TCPConnection::*p)(const std::string &message) = &TCPConnection::sendInLoop;
                loop_->runInLoop(std::bind(p,this,buf->retrieveAllAsString()));
            }
        }
    }

    void TCPConnection::send(const std::string &buf) {
        if (state_ == kConnected) {
            if (loop_->isInLoopThread()) {
                sendInLoop(buf.c_str(), buf.size());
            } else {
                void (TCPConnection::*p)(const void *data, size_t len) = &TCPConnection::sendInLoop;
                loop_->runInLoop(std::bind(p,
                                           this,
                                           buf.c_str(),
                                           buf.size()));
            }
        }
    }

    void TCPConnection::shutdown() {
        if(state_ == kConnected){
            setState(kDisConnecting);
            loop_->queueInLoop(std::bind(&TCPConnection::shutdownInLoop, this));
        }
    }

    void TCPConnection::ConnectEstablish() {
        setState(kConnected);
        /**
          * channel_->tie(shared_from_this());
          * tie相当于在底层有一个强引用指针记录着，防止析构
          * 为了防止TcpConnection这个资源被误删掉，而这个时候还有许多事件要处理
          * channel->handleEvent 会进行一次判断，是否将弱引用指针变成强引用，变成得话就防止引用计数为0而被析构得可能
          */
        channel_->tie(shared_from_this());
        channel_->enableReadEvent();

        connectionCallBack_(shared_from_this());
    }

    void TCPConnection::ConnectDestroy() {
        if (state_ == kConnected) {
            setState(kDisConnected);
            channel_->disAllEvent();
            connectionCallBack_(shared_from_this());
        }
        channel_->remove();
    }

    void TCPConnection::handleRead(Timestamp receiveTime) {
        int savedErrno = 0;
        // TcpConnection会从socket读取数据，然后写入inpuBuffer
        ssize_t n = inputBuffer_.readfd(channel_->fd(), &savedErrno);
        if (n > 0) {
            // 已建立连接的用户，有可读事件发生，调用用户传入的回调操作
            // TODO:shared_from_this
            messageCallBack_(shared_from_this(), &inputBuffer_, receiveTime);
        } else if (n == 0) {
            // 没有数据，说明客户端关闭连接
            handleClose();
        } else {
            // 出错情况
            errno = savedErrno;
            LOG_ERROR("TcpConnection::handleRead() failed\n");
            handleError();
        }
    }

    void TCPConnection::handelWrite() {
        if (channel_->isWriting()) {
            ssize_t n = ::write(channel_->fd(),
                                outputBuffer_.peek(),
                                outputBuffer_.readableBytes());
            if (n > 0) {
                //重置readerIndex_的位置，后移n个字节，如果写完就重置位
                outputBuffer_.retrieve(n);
                if (outputBuffer_.readableBytes() == 0) {
                    //说明已经将数据全部写入channel了,关闭channel可写
                    channel_->disableWriteEvent();
                    if (writeCompleteCallBack_) {
                        //函数结束后调用回调
                        loop_->queueInLoop(std::bind(&TCPConnection::writeCompleteCallBack_,
                                                     shared_from_this()));
                    }
                    if (state_ == kDisConnecting) {
                        shutdownInLoop();
                    }
                } else {
                    LOG_ERROR("TCPConnection::handelWrite failed\n");
                }
            } else {
                LOG_ERROR("TCPConnection::handelWrite fd=[%d]\n", channel_->fd());
            }
        }
    }

    //在连接关闭的时候poller通知channel调用closeEventCallBack_函数，closeEventCallBack_是由TCPConnection::handleClose注册的
    //所以实际上在连接关闭的时候会调用这个函数
    void TCPConnection::handleClose() {
        LOG_INFO("TCPConnection::handleClose fd=%d, sate=%s \n",channel_->fd(),StateToString().c_str());
        setState(kDisConnected);
        channel_->disAllEvent();

        TCPConnectionPtr connPtr(shared_from_this());
        //连接关闭的回调
        connectionCallBack_(connPtr);
        //关闭连接,执行TCPServer::removeConnection
        closeCallBack_(connPtr);
    }

    void TCPConnection::handleError() {
        int err = 0;
        int optval = 0;
        socklen_t optlen = sizeof(optval);
        if (::getsockopt(channel_->fd(), SOL_SOCKET, SO_ERROR, &optval, &optlen)) {
            err = errno;
        } else {
            err = optval;
        }
        LOG_ERROR("TCPConnection::handleError name[%s],SO_ERROR=%d\n", name_.c_str(), err);

    }

    void TCPConnection::sendInLoop(const std::string &message) {
        sendInLoop(message.data(),message.size());
    }

    void TCPConnection::sendInLoop(const void *message, size_t len) {
        int nwrote = 0;
        int remaining = len;
        bool defaultError = false;
        if (state_ == kDisConnected) {
            LOG_ERROR("TCPConnection is close give up writing");
        }
        //如果这是第一次发送数据,并且缓冲区中没有数据
        if (!channel_->isWriting() && outputBuffer_.readableBytes() == 0) {
            nwrote = ::write(channel_->fd(), message, len);
            if (nwrote >= 0) {
                remaining = len - nwrote;
                //一次直接将数据全部写完了,那就直接执行回调就好了
                if (remaining == 0 && writeCompleteCallBack_) {
                    loop_->queueInLoop(std::bind(writeCompleteCallBack_, shared_from_this()));
                }
            } else {
                //写入出错
                nwrote = 0;
                if (errno != EWOULDBLOCK)//排除因为非阻塞正常返回导致的错误
                {
                    if (errno == EPIPE || errno == ECONNRESET) {
                        defaultError = true;
                    }
                }
            }
        }
        //write并没有一次性发送完,需要将剩余的数据存到buffer中然后给channel注册epollout事件
        //poller发现tcp的发送缓冲区还有空间,会通知相应的sock-channel执行相应的writeEventCallBack_回调
        //也就是handleWrite_,直到把缓冲区中的数据全部发送完毕
        if (!defaultError && remaining > 0) {
            //剩余的待发送数据长度
            size_t oldLen = outputBuffer_.readableBytes();
            if (oldLen + remaining > highWaterMark_ &&
                oldLen < highWaterMark_ &&
                highWaterMarkCallBack_) {
                loop_->queueInLoop(std::bind(TCPConnection::highWaterMarkCallBack_,
                                             shared_from_this(),
                                             oldLen + remaining));
            }
            outputBuffer_.append((char *) message + nwrote, remaining);
            if (!channel_->isWriting()) {
                channel_->enableWriteEvent();//给channel注册读事件,这样channel才会去调用writeEventCallBack_才能将数据全部发送完毕
            }
        }
    }

    void TCPConnection::shutdownInLoop() {
        //outputBuffer中的数据全部写完。
        if(!channel_->isWriting()){
            socket_->shutDownWrite();
        }
    }
}