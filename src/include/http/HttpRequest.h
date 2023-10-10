#ifndef HTTPREQUEST_H_
#define HTTPREQUEST_H_

#include <string>
#include <unordered_map>

#include "Timestamp.h"
#include "noncopyable.h"

class HttpRequest {
 private:
  /* data */
 public:
  enum Method { kInvalid, kGet, kPost, kHead, kPut, kDelete };
  enum Version { kUnknow, kHttp10, kHttp11 };

  HttpRequest() : method_(kInvalid), version_(kUnknow) {}

  bool setMethod(const char *start, const char *end) {
    std::string method(start, end);
#define XX(Me, m)         \
  if (method == #m) {     \
    method_ = Method::Me; \
  }
    XX(kGet, get);
    XX(kPost, post);
    XX(kHead, head);
    XX(kPut, put);
    XX(kDelete, Delete);

    XX(kGet, GET);
    XX(kPost, POST);
    XX(kHead, HEAD);
    XX(kPut, PUT);
    XX(kDelete, DELETE);
#undef XX
    return method_ != kInvalid;
  }

  const char *MethodToString() const {
    switch (method_) {
#define XX(name)     \
  case Method::name: \
    return #name;    \
    break;
      XX(kGet);
      XX(kPost);
      XX(kHead);
      XX(kPut);
      XX(kDelete);
#undef XX
      default:
        return "kInvalid";
    }
    return "ERROR";
  }

  void setVersion(Version v) { version_ = v; }
  Version version() const { return version_; }

  void setPath(const char *start, const char *end) { path_.assign(start, end); }
  const std::string path() const { return path_; }

  void setQuery(const char *start, const char *end) {
    query_.assign(start, end);
  }
  const std::string &query() const { return query_; }

  void setReceiveTime(Timestamp receiveTime) { receiveTime_ = receiveTime; }
  Timestamp receiveTime() const { return receiveTime_; }

  void addHeader(const char *start, const char *colon, const char *end) {
    std::string field(start, colon);
    ++colon;

    while (colon < end && isspace(*colon)) {
      ++colon;
    }
    std::string value(colon, end);
    while (!value.empty() && isspace(value[value.size() - 1])) {
      value.pop_back();
    }
    headers_[field] = value;
  }

  std::string getHeader(const std::string &field) const {
    std::string result;
    auto it = headers_.find(field);
    if (it != headers_.end()) {
      result = it->second;
    }
    return result;
  }

  const std::unordered_map<std::string, std::string> headers() const {
    return headers_;
  }

  void swap(HttpRequest &rhs) {
    std::swap(method_, rhs.method_);
    std::swap(version_, rhs.version_);
    path_.swap(rhs.path_);
    query_.swap(rhs.query_);
    std::swap(receiveTime_, rhs.receiveTime_);
    headers_.swap(rhs.headers_);
  }

 private:
  Method method_;                                         // 请求方式
  Version version_;                                       // http版本
  std::string path_;                                      // 请求路径
  std::string query_;                                     // 请求参数
  Timestamp receiveTime_;                                 // 请求时间
  std::unordered_map<std::string, std::string> headers_;  // 请求头列表
};

#endif  // !HTTPREQUEST_H_
