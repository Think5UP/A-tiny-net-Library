//
// Created by root on 2/16/23.
//

#include <iostream>

#include "../net/InetAddress.h"
int main(){
    net_lib::InetaAddress inetaAddress(8080);
    std::string str = inetaAddress.toIpPort();
    std::cout <<str << std::endl;
}
