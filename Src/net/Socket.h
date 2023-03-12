//
// Created by root on 3/1/23.
//

#ifndef NET_LIB_SOCKET_H
#define NET_LIB_SOCKET_H

#include "../Base/nocopyable.h"

namespace net_lib{

    class InetaAddress;

    class Socket : noncopyable{
    public:
        Socket(int sockfd) : sockfd_(sockfd) {}
        ~Socket();

        int fd() const {return sockfd_;}

        void bindAddress(const InetaAddress &localAddress);
        void listen();
        int accept(InetaAddress* peerAddress);

        void shutDownWrite();
        void setTCPNoDelay(bool on);
        void setReuseAddr(bool on);
        void setReusePort(bool on);
        void setKeepAlive(bool on );
    private:
        const int sockfd_;
    };
}

#endif //NET_LIB_SOCKET_H
