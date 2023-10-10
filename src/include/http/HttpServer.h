#ifndef HTTPSERVER_H_
#define HTTPSERVER_H_

#include <string>

#include "HttpResponse.h"
#include "Logging.h"
#include "TcpServer.h"
#include "noncopyable.h"

class HttpRequest;
class HttpResponse;

class HttpServer : noncopyable {
 public:
  using HttpCallback = std::function<void(const HttpRequest&, HttpResponse*)>;

  HttpServer(EventLoop* loop, const InetAddress& listenAddr,
             const std::string& name,
             TcpServer::Option option = TcpServer::kNoReusePort);

  EventLoop* getLoop() const { return server_.getLoop(); }

  void setHttpCallback(const HttpCallback& cb) { httpCallback_ = cb; }

  void start();

 private:
  void onConnection(const TcpConnectionPtr& conn);
  void onMessage(const TcpConnectionPtr& conn, Buffer* buf,
                 Timestamp receiveTime);
  void onRequest(const TcpConnectionPtr&, const HttpRequest&);

  TcpServer server_;
  HttpCallback httpCallback_;
};

#endif  // !HTTPSERVER_H_