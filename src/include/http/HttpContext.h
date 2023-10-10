#ifndef HTTPCONTEXT_H_
#define HTTPCONTEXT_H_

#include "HttpRequest.h"

class Buffer;

class HttpContext {
 public:
  enum HttpRequestParseState {
    kExpectRequestLine,  // 请求行解析
    kExpectHeader,       // 请求头解析
    kExpectBody,         // 请求体解析
    kGotAll              // 解析完毕
  };
  HttpContext() : state_(kExpectRequestLine) {}
  ~HttpContext() {}

  bool parseRequest(Buffer *buffer, Timestamp receiveTime);

  bool gotAll() const { return state_ == kGotAll; }

  void reset() {
    state_ = kExpectRequestLine;
    HttpRequest dump;
    request_.swap(dump);
  }

  const HttpRequest &request() const { return request_; }

 private:
  bool processRequestLine(const char *begin, const char *end);

  HttpRequestParseState state_;
  HttpRequest request_;
};

#endif  // !HTTPCONTEXT_H_