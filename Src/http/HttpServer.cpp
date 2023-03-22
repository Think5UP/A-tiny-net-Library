//
// Created by root on 3/22/23.
//
#include <memory>
#include <iostream>

#include "HttpServer.h"
#include "HttpContext.h"
#include "HttpRequest.h"
#include "HttpResponse.h"

//设置默认的响应状态码、响应信息并关闭响应连接
void defaultHttpCallBack(const HttpRequest &,HttpResponse *resp){
    resp->setStatusCode(HttpResponse::k404NotFound);
    resp->setStatusMessage("Not Found");
    resp->setCloseConnection(true);
}

HttpServer::HttpServer(net_lib::EventLoop *loop, const net_lib::InetaAddress &listenAddr,
                       const std::string &name,net_lib::TCPServer::Option opetion)
        : server_(loop,listenAddr,name,opetion){
    server_.setConnectionCallBack(
            std::bind(&HttpServer::onConnection,this,std::placeholders::_1)
    );
    server_.setMessageCallBack(
            std::bind(&HttpServer::onMessage,this,
                      std::placeholders::_1,
                      std::placeholders::_2,
                      std::placeholders::_3)
    );
    server_.setThreadNum(4);
}

void HttpServer::start() {
    LOG_INFO("HttpServer [%s],starts listening on %s",server_.name().c_str(),server_.ipPort().c_str());
    server_.start();
}

void HttpServer::onConnection(const net_lib::TCPConnectionPtr &conn) {
    if(conn->connected()){
        LOG_INFO("new Connection arrived");
    } else {
        LOG_INFO("Connection close");
    }
}

void HttpServer::onMessage(const net_lib::TCPConnectionPtr &conn,
                      net_lib::Buffer *buf,
                      net_lib::Timestamp receiveTime) {
    std::unique_ptr<HttpContext> context(new HttpContext);
#if 0
    std::string request = buf->GetBufferAllAsString();
    std::cout << request << std::endl;
#endif
    if(!context->parseRequest(buf,receiveTime)){
        LOG_INFO("parseRequest failed");
        conn->send("HTTP/1.1 400 Bad Request\r\n\r\n");
        conn->shutdown();
    }

    if(context->gotAll()){
        LOG_INFO("parseRequest success");
        onRequest(conn,context->getRequest());
        context.reset();
    }
}

void HttpServer::onRequest(const net_lib::TCPConnectionPtr &conn, const HttpRequest &req) {
    //判断长连接还是短链接
    const std::string &Connection = req.getHeader("Connection");
    bool close = Connection == "close" ||
            (req.version() == HttpRequest::kHttp10 && Connection != "keep-Alive");
    HttpResponse response(close);
    //处理回调，然后将请求重新装填进response，发送给客户端
    httpCallBack_(req, &response);
    net_lib::Buffer buf;
    response.appendToBuffer(&buf);
    conn->send(&buf);
    //短链接处理完之后直接关闭连接
    if(response.CloseConnection()){
        conn->shutdown();
    }

}