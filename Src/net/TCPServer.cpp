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
        acceptor_->setNewConnectionCallBack(std::bind(&TCPServer::newConnection,this,
                                                      std::placeholders::_1,std::placeholders::_2));
    }

    TCPServer::~TCPServer() {

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

    void TCPServer::newConnection(int sockfd, const InetaAddress &peeraddr) {

    }

    void TCPServer::removeConnection(const TCPConnectionPtr &conn) {

    }

    void TCPServer::removeConnectionInLoop(const TCPConnectionPtr &conn) {

    }
}

