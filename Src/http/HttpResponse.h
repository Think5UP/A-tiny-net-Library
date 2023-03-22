//
// Created by root on 3/20/23.
//
#ifndef NET_LIB_HTTPRESPONSE_H
#define NET_LIB_HTTPRESPONSE_H

#include <map>

#include "../Base/copyable.h"

namespace net_lib{
    class Buffer;
}

class HttpResponse : public net_lib::copyable{
public:
    enum HttpStatusCode{
        kUnknown,
        k2000k = 200,
        k301MovedPermanently = 301,
        k400BadRequest = 400,
        k404NotFound = 404,
    };
    explicit HttpResponse(bool close) : statusCode_(kUnknown),
                                        closeConnection_(close){

    }

    void setStatusCode(HttpStatusCode code) { statusCode_ = code; }
    void setStatusMessage(const std::string &message) { statusMessage_ = message; }
    void setCloseConnection(bool on) { closeConnection_ = on; }
    bool CloseConnection() const { return closeConnection_; }

    void addHeader(const std::string &key,const std::string &value) {
        headers_[key] = value;
    }
    void setContentType(const std::string &ContentType) { addHeader("Content-Type",ContentType); }

    void setBody(const std::string &body) { body_ = body; }

    void appendToBuffer(net_lib::Buffer* output);

private:
    std::map<std::string,std::string> headers_; // 响应头部，键值对
    HttpStatusCode statusCode_;                 // 响应行 - 状态码
    std::string statusMessage_;                 // 响应行 - 状态码
    bool closeConnection_;                      // 是否关闭连接
    std::string body_;                          // 响应体
};
#endif //NET_LIB_HTTPRESPONSE_H
