#ifndef LOGSTREAM_H_
#define LOGSTREAM_H_

#include <string>

#include "FixedBuffer.h"
#include "noncopyable.h"

class GeneralTemplate : noncopyable {
 public:
  GeneralTemplate() : data_(nullptr), len_(0) {}

  explicit GeneralTemplate(const char *data, int len)
      : data_(data), len_(len) {}

  const char *data_;
  int len_;
};

class LogStream : noncopyable {
 public:
  using Buffer = detail::FixedBuffer<detail::kSmallBuffer>;
  void append(const char *data, int len) { buffer_.append(data, len); }
  const Buffer &buffer() const { return buffer_; }
  void resetBuffer() { buffer_.reset(); }

  /**
   * 重载operator << 将不同格式数据转化为字符串，并存入 LogStream::buffer_
   */
  LogStream &operator<<(short v);
  LogStream &operator<<(unsigned short v);
  LogStream &operator<<(int v);
  LogStream &operator<<(unsigned int v);
  LogStream &operator<<(long v);
  LogStream &operator<<(unsigned long v);
  LogStream &operator<<(long long v);
  LogStream &operator<<(unsigned long long v);

  LogStream &operator<<(float v);
  LogStream &operator<<(double v);

  LogStream &operator<<(char c);
  LogStream &operator<<(const void *data);
  LogStream &operator<<(const char *str);
  LogStream &operator<<(const unsigned char *str);
  LogStream &operator<<(const std::string &str);
  LogStream &operator<<(const Buffer &buf);

  // (const char*, int)的重载
  LogStream &operator<<(const GeneralTemplate &g);

 private:
  static const int kMaxNumericSize = 48;

  // 对整型的特殊处理
  template <typename T>
  void formatInteger(T);

  Buffer buffer_;
};

#endif  // !LOGSTREAM_H_