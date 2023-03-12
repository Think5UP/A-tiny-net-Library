//
// Created by root on 2/16/23.
//


#include <string.h>
#include <strings.h>


#include "InetAddress.h"

namespace net_lib{

    InetaAddress::InetaAddress(uint16_t port, std::string ip) {
        bzero(&address_, sizeof(address_));
        address_.sin_family = AF_INET;
        address_.sin_port = htons(port);
        address_.sin_addr.s_addr = inet_addr(ip.c_str());
    }

    std::string InetaAddress::toIp() const {
        char buf[64] {0};
        ::inet_ntop(AF_INET,&address_.sin_addr,buf,sizeof(buf));
        return buf;
    }

    std::string InetaAddress::toIpPort() const {
        char buf[64]{0};
        ::inet_ntop(AF_INET,&address_.sin_addr,buf,sizeof(buf));
        size_t end = strlen(buf);
        uint16_t port = ntohs(address_.sin_port);
        sprintf(buf + end,":%u",port);
        return buf;
    }

    uint16_t InetaAddress::toPort() const {
        return ntohs(address_.sin_port);
    }
}

