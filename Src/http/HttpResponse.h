//
// Created by root on 3/20/23.
//

#ifndef NET_LIB_HTTPRESPONSE_H
#define NET_LIB_HTTPRESPONSE_H

#include <map>

#include "../Base/copyable.h"

class Buffer;
class HttpResponse : public net_lib::copyable{
public:
    enum HttpStatusCode{
        kUnknown,
        k2000k = 200;
        k301MovedPermanently = 301,
        k400BadRequest = 400,
        k404NotFound = 404,
    };
private:
    std::map<std::string,std::string> headers_; // 响应头部，键值对
    HttpStatusCode statusCode_;                 // 响应行 - 状态码
    std::string statusMessage_;                 // 响应行 - 状态码
    bool closeConnection_;                      // 是否关闭连接
    std::string body_;                          // 响应体
};

#endif //NET_LIB_HTTPRESPONSE_H
