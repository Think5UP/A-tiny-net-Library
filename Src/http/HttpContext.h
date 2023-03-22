//
// Created by root on 3/21/23.
//

#ifndef NET_LIB_HTTPCONTEXT_H
#define NET_LIB_HTTPCONTEXT_H

#include "HttpRequest.h"
#include "../Base/copyable.h"

namespace net_lib{
    class Buffer;
}

//要关注如何解析Buffer中的文本(请求行、请求头)部分、请求体(可能是二进制或其他文本格式).
// 一个正常的请求，一般至少是有请求行的，默认解析状态为kExpectRequestLine
class HttpContext : public net_lib::copyable {
public:
    enum HttpRequestParseState {
        kExpectRequestLine,
        kExpectHeader,
        kExpectBody,
        kGotAll
    };

    HttpContext() : state_(kExpectRequestLine) {}

    //解析请求
    //传入需要解析的Buffer对象和接收时间，根据期望解析的部分进行处理。
    bool parseRequest(net_lib::Buffer *buf,net_lib::Timestamp receiveTime);

    bool gotAll() const { return kGotAll == state_; }

    //重置HttpContext状态,为了复用HttpContext
    void reset() {
        state_ = kExpectRequestLine;
        HttpRequest request;
        request_.swap(request);
    }

    const HttpRequest &getRequest() const { return request_; }
    HttpRequest &getRequest() { return request_; }

private:
    //请求行的解析
    bool processRequestLine(const char *begin,const char *end);

    HttpRequestParseState state_;
    HttpRequest request_;
};

#endif //NET_LIB_HTTPCONTEXT_H
