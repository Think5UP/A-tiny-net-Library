//
// Created by root on 3/1/23.
//

#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/tcp.h>

#include "Socket.h"
#include "../Base/Logger.h"
#include "InetAddress.h"

namespace net_lib{
    Socket::~Socket() {
        ::close(sockfd_);
    }

    void Socket::bindAddress(const InetaAddress &localAddress){
        if(0 != ::bind(sockfd_,(sockaddr *)localAddress.getSockAddress(), sizeof(sockaddr_in))){
            LOG_FATAL("bind sockfd:  %d fail\n",sockfd_);
        }
    }
    void Socket::listen(){
        if(0 != ::listen(sockfd_,1024)){
            LOG_FATAL("listen sockfd:  %d fail\n",sockfd_);
        }
    }
    int Socket::accept(InetaAddress* peerAddress){
        sockaddr_in addr;
        socklen_t len = sizeof(addr);
        ::memset(&addr,0,sizeof(addr));
        int connfd = ::accept4(sockfd_,(sockaddr *)&addr,&len,SOCK_NONBLOCK | SOCK_CLOEXEC);
        if(connfd >= 0){
            peerAddress->setSockAddress(addr);
        } else {
            LOG_FATAL("accept4() failed\n");
        }
        return connfd;
    }
    //关闭sockfd的写端，关闭之后只能从客户端读数据
    void Socket::shutDownWrite(){
        if(::shutdown(sockfd_,SHUT_WR) < 0){
            LOG_ERROR("shutdownWrite() error\n");
        }
    }
    void Socket::setTCPNoDelay(bool on){
        int optval = on ? 1 : 0;
        ::setsockopt(sockfd_,IPPROTO_TCP,TCP_NODELAY,&optval, sizeof(optval));
    }
    void Socket::setReuseAddr(bool on){
        int optval = on ? 1 : 0;
        ::setsockopt(sockfd_,SOL_SOCKET,SO_REUSEADDR,&optval, sizeof(optval));
    }
    void Socket::setReusePort(bool on){
        int optval = on ? 1 : 0;
        ::setsockopt(sockfd_,SOL_SOCKET,SO_REUSEPORT,&optval, sizeof(optval));
    }
    void Socket::setKeepAlive(bool on ){
        int optval = on ? 1 : 0;
        ::setsockopt(sockfd_,SOL_SOCKET,SO_KEEPALIVE,&optval, sizeof(optval));
    }
}
