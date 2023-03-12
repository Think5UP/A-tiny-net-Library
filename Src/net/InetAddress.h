//
// Created by root on 2/16/23.
//

#ifndef NET_LIB_INETADDRESS_H
#define NET_LIB_INETADDRESS_H

#include <string>
#include <arpa/inet.h>
#include <netinet/in.h>

namespace net_lib{

    class InetaAddress{
    public:
        explicit InetaAddress(uint16_t port = 0,std::string ip = "127.0.0.1");

        explicit InetaAddress(const sockaddr_in& address) : address_(address){}

        std::string toIp() const;
        std::string toIpPort() const;
        uint16_t toPort() const;

        const sockaddr_in *getSockAddress() const {return &address_;}
        void setSockAddress(const sockaddr_in& addr) { address_ = addr; }
    private:
        struct sockaddr_in address_;
    };

}



#endif //NET_LIB_INETADDRESS_H
