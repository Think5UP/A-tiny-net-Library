#include "HttpResponse.h"

#include <cstdio>
#include <cstring>

#include "Buffer.h"

void HttpResponse::appendToBuffer(Buffer *output) const {
  char buf[32];
  //响应行
  memset(buf, '\0', sizeof(buf));
  snprintf(buf, sizeof(buf), "Http/1.1 %d", statusCode_);
  output->append(buf);
  output->append(statusMessage_);
  output->append("\r\n");

  //响应头部
  if (closeConnection_) {
    output->append("Connection: Close");
  } else {
    snprintf(buf, sizeof(buf), "Content-Length: %zd\r\n", body_.size());
    output->append(buf);
    output->append("Connection: keep-Alive\r\n");
  }
  for (const auto &header : headers_) {
    output->append(header.first);
    output->append(":");
    output->append(header.second);
    output->append("\r\n");
  }
  output->append("\r\n");  //空行
  output->append(body_);   //响应体
}