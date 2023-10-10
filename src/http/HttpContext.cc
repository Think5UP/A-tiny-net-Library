#include "HttpContext.h"

#include <iterator>

#include "Buffer.h"

bool HttpContext::parseRequest(Buffer *buffer, Timestamp receiveTime) {
  bool ok = true;
  bool hasMore = true;
  while (hasMore) {
    //解析请求行
    if (state_ == kExpectRequestLine) {
      //查找buffer中第一次出现\r\n的位置
      const char *crlf = buffer->findCRLF();
      //找到了
      if (crlf) {
        //解析请求行中的内容，打成HttpRequest
        ok = processRequestLine(
            buffer->peek(),
            crlf);  //对readerIndex_到第一个找到CRLF位置的地方处理请求行
        if (ok) {
          request_.setReceiveTime(receiveTime);
          //将buffer的readrIndex_移动到crlf+2的位置开始解析请求头
          buffer->retrieveUntil(crlf + 2);
          //改变状态开始解析请求头
          state_ = kExpectHeader;
        } else {
          hasMore = false;
        }
      } else {
        hasMore = false;
      }
    } else if (state_ == kExpectHeader) {  //开始解析请求头
      //找到了请求头的CRLF
      const char *crlf = buffer->findCRLF();
      if (crlf) {
        const char *colon = std::find(buffer->peek(), crlf, ':');
        //找到了分隔符
        if (colon != crlf) {
          request_.addHeader(buffer->peek(), colon, crlf);
        } else {
          state_ = kExpectBody;
        }
        buffer->retrieveUntil(crlf + 2);
      } else {
        hasMore = false;
      }
    } else if (state_ == kExpectBody) {
      //如果buffer中还有数据那剩下的一定是请求体
      if (buffer->readableBytes()) {
        request_.setQuery(buffer->peek(), buffer->beginWrite());
      }
      state_ = kGotAll;
      hasMore = false;
    }
  }
  return ok;
}

bool HttpContext::processRequestLine(const char *begin, const char *end) {
  bool succeed = false;
  const char *start = begin;
  const char *space = std::find(start, end, ' ');
  if (space != end && request_.setMethod(start, space)) {
    start = space + 1;
    space = std::find(start, end, ' ');
    if (space != end) {
      const char *question = std::find(start, space, '?');
      request_.setPath(start, question);
      if (question != space) {
        request_.setQuery(question, space);
      }
      start = space + 1;
      succeed = (end - start == 8 && std::equal(start, end - 1, "Http/1."));
      if (succeed) {
        if (*(end - 1) == '1') {
          request_.setVersion(HttpRequest::kHttp11);
          return succeed;
        } else if (*(end - 1) == '0') {
          request_.setVersion(HttpRequest::kHttp10);
          return succeed;
        }
        succeed = false;
        return succeed;
      }
    }
  }
  return succeed;
}
