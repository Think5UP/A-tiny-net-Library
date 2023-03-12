//
// Created by root on 3/2/23.
//

#ifndef NET_LIB_ACCEPTOR_H
#define NET_LIB_ACCEPTOR_H

#include <functional>

#include "Socket.h"
#include "Channel.h"
#include "../Base/nocopyable.h"

namespace net_lib{

    class EventLoop;
    class InetaAddress;

    class Acceptor : noncopyable{
    public:
        typedef std::function<void(int sockfd,const InetaAddress&)> NewConnectionCallBack;

        Acceptor(EventLoop* loop,const InetaAddress& listenAddr,bool reusePort);
        ~Acceptor();
        void listen();

        void setNewConnectionCallBack(const NewConnectionCallBack& cb) { newConnectionCallBack_ = cb; }

    private:
        void handleRead();
        EventLoop *loop_;
        bool listening_;
        Socket acceptSocket_;
        Channel acceptChannel_;
        NewConnectionCallBack newConnectionCallBack_;
    };
}



#endif //NET_LIB_ACCEPTOR_H
