//
// Created by root on 3/2/23.
//
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "../Base/Logger.h"
#include "Acceptor.h"
#include "EventLoop.h"
#include "InetAddress.h"


int createNonBlocking(){
    int sockfd = ::socket(AF_INET,SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC,IPPROTO_TCP);
    if(sockfd < 0){
        LOG_FATAL("%s%s%d sock create error",__FILE__,__FUNCTION__,errno);
    }
    return sockfd;
}


namespace net_lib{
    Acceptor::Acceptor(EventLoop *loop,
                       const InetaAddress &listenAddr,
                       bool reusePort) : loop_(loop),
                                         listening_(false),
                                         acceptSocket_(createNonBlocking()),
                                         acceptChannel_(loop,acceptSocket_.fd()){
        LOG_INFO("%s:%s has create a new nonBlocking socketFd %d",__FILE__,__FUNCTION__,acceptSocket_.fd());
        acceptSocket_.setKeepAlive(true);
        acceptSocket_.setReuseAddr(true);
        acceptSocket_.setReusePort(true);
        acceptChannel_.setReadEventCallBack(std::bind(&Acceptor::handleRead, this));
    }

    Acceptor::~Acceptor() {
        //关闭事件
        acceptChannel_.disAllEvent();
        //将channelremove
        acceptChannel_.remove();
    }

    void Acceptor::listen() {
        listening_ = true;
        acceptSocket_.listen();
        acceptChannel_.enableReadEvent();
    }

    void Acceptor::handleRead() {
        InetaAddress peerAddr;
        int connfd = acceptSocket_.accept(&peerAddr);
        if(connfd > 0){
            if(newConnectionCallBack_){
                newConnectionCallBack_(connfd,peerAddr);
            } else {
                LOG_ERROR("%s:%s no setting newConnectionCallBack() function",__FILE__,__FUNCTION__ );
                ::close(connfd);
            }
        } else {
            LOG_ERROR("accept failed");
            //当前进程的fd使用光了就会将errno设置为EMFILE
            //需要提高服务器fd上上限
            if(errno == EMFILE){
                LOG_ERROR("sockfd reach limit");
            }
        }
    }
}