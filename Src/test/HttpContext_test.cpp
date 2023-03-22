//
// Created by root on 3/21/23.
//
#include <string>
#include <iostream>

#include "../net/Buffer.h"
#include "../Base/Timestamp.h"
#include "../http/HttpContext.h"

int main(){
    net_lib::Buffer buf;
    std::string all("GET /index.html HTTP/1.1\r\n"
               "Host: www.chenshuo.com\r\n"
               "\r\n"
               "xxx");
    buf.append(all);
    std::string request = buf.GetBufferAllAsString();
    std::cout << request << std::endl;
    std::cout << "--------------" << std::endl;
    HttpContext context;
    context.parseRequest(&buf,net_lib::Timestamp::now());
    std::cout << context.getRequest().getHeader("Host") << std::endl;
    std::cout << context.gotAll() << std::endl;
}