//
// Created by root on 3/22/23.
//
#ifndef NET_LIB_HTTPSERVER_H
#define NET_LIB_HTTPSERVER_H

#include <string>
#include <functional>

#include "../Base/Logger.h"
#include "../net/TCPServer.h"
#include "../Base/noncopyable.h"

class HttpRequest;
class HttpResponse;

class HttpServer : net_lib::noncopyable{
public:
    typedef std::function<void (const HttpRequest &, HttpResponse *)> HttpCallBack;
    HttpServer(net_lib::EventLoop* loop,
               const net_lib::InetaAddress &listenAddr,
               const std::string &name,
               net_lib::TCPServer::Option opetion = net_lib::TCPServer::kNoReusePort);

    net_lib::EventLoop *getLoop() const { return server_.getLoop(); }
    void setThreadNum(int numThreads) { server_.setThreadNum(numThreads); }

    void setHttpCallBack(const HttpCallBack &cb){
        httpCallBack_ = cb;
    }

    void start();

private:

    void onConnection(const net_lib::TCPConnectionPtr &conn);

    void onMessage(const net_lib::TCPConnectionPtr &conn,
                   net_lib::Buffer *buf,
                   net_lib::Timestamp receiveTime);

    void onRequest(const net_lib::TCPConnectionPtr &conn, const HttpRequest &);

    net_lib::TCPServer server_;
    HttpCallBack httpCallBack_;
};

#endif //NET_LIB_HTTPSERVER_H
