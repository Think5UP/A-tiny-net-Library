//
// Created by root on 2/20/23.
//

#include "TCPServer.h"
#include "../Base/Logger.h"

namespace net_lib{

    static EventLoop* checkNotNull(EventLoop* loop){
        if(loop == nullptr){
            LOG_FATAL("%s:%s:%d mainLoop is null",__FILE__, __FUNCTION__, __LINE__);
        }
        return loop;
    }

    TCPServer::TCPServer(EventLoop *loop, const InetaAddress &listenAddr,
                         const std::string &name,
                         Option option) : loop_(checkNotNull(loop)),
                                          ipPort_(listenAddr.toIpPort()),
                                          name_(name),
                                          threadPool_(new EventLoopThreadPool(loop,name_)),
                                          acceptor_(new Acceptor(loop,listenAddr,option == kReusePort)),
                                          connectionCallBack_(),
                                          messageCallBack_(),
                                          writeCompleteCallBack_(),
                                          threadInitCallBack_(),
                                          started_(0),
                                          nextConnId_(1){
        //将newConnection注册给acceptor_中的newConnectionCallBack_回调，当acceptor_监听到新连接会执行newConnectionCallBack_
        acceptor_->setNewConnectionCallBack(std::bind(&TCPServer::newConnection,this,
                                                      std::placeholders::_1,std::placeholders::_2));
    }

    TCPServer::~TCPServer() {
        for(auto &item : connections_){
            TCPConnectionPtr conn(item.second);
            item.second.reset();
            conn->getLoop()->runInLoop(std::bind(&TCPConnection::ConnectDestroy,conn));
        }
    }

    void TCPServer::start() {
        if(started_++ == 0){
            threadPool_->start(threadInitCallBack_);
            loop_->runInLoop(std::bind(&Acceptor::listen, acceptor_.get()));
        }
    }

    void TCPServer::setThreadNum(int numThreads) {
        threadPool_->setThreadNum(numThreads);
    }

    //acceptor在监听到有新的客户端处理handleRead回调的时候接就会执行这个回调，这个回调在构造函数会注册给acceptor的newConnectionCallBack_
    void TCPServer::newConnection(int sockfd, const InetaAddress &peeraddr) {
        EventLoop *ioloop = threadPool_->getNextLoop();
        char buff[64] = {0};
        snprintf(buff, sizeof(buff),"-%s#%d",ipPort_.c_str(),nextConnId_);
        ++nextConnId_;
        std::string connName = name_ + buff;
        LOG_INFO("TCPServer::newConnection [%s] - New connection [%s] from %s \n",
                 name_.c_str(),
                 connName.c_str(),
                 peeraddr.toIpPort().c_str());

        InetaAddress localAddr([sockfd](){
            sockaddr_in local;
            ::bzero(&local, sizeof(local));
            socklen_t addrlen = sizeof(local);
            if(::getsockname(sockfd,(sockaddr *)&local,&addrlen) < 0){
                LOG_ERROR("getLocalAddr Error");
            }
            return local;
        }());

        TCPConnectionPtr conn(new TCPConnection(ioloop,
                                                connName,
                                                sockfd,
                                                localAddr,
                                                peeraddr));
        conn->setConnectionCallBack(connectionCallBack_);
        conn->setMessageCallBack(messageCallBack_);
        conn->setWriteCompleteCallBack(writeCompleteCallBack_);
        //关闭连接的回调
        conn->setCloseCallBack(std::bind(&TCPServer::removeConnection,this,std::placeholders::_1));
        //这里会直接调用TCPConnection::ConnectEstablish,将channel和conn绑定,并且将状态设置为connected
        ioloop->runInLoop(std::bind(&TCPConnection::ConnectEstablish, conn));
    }

    void TCPServer::removeConnection(const TCPConnectionPtr &conn) {
        loop_->runInLoop(std::bind(&TCPServer::removeConnectionInLoop, this, conn));
    }

    void TCPServer::removeConnectionInLoop(const TCPConnectionPtr &conn) {
        LOG_INFO("TCPServer::removeConnectionInLoop [%s] - connection %s",
                 name_.c_str(),conn->getName().c_str());
        size_t n = connections_.erase(conn->getName());
        if(n == 1){
            EventLoop *ioloop = conn->getLoop();
            ioloop->queueInLoop(std::bind(&TCPConnection::ConnectDestroy,conn));
        } else {
            LOG_ERROR("connections_.erase error %s-%s-%d \n",__FILE__,__FUNCTION__ ,__LINE__);
        }
    }
}

