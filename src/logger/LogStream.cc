#include "LogStream.h"

#include <algorithm>

using namespace detail;

static const char digits[] = {'9', '8', '7', '6', '5', '4', '3', '2', '1', '0',
                              '1', '2', '3', '4', '5', '6', '7', '8', '9'};

template <typename T>
void LogStream::formatInterger(T num) {
  if (buffer_.avail() >= kMaxNumericSize) {
    char *start = buffer_.current();
    char *cur = start;
    const char *zero = digits + 9;
    bool negative = (num < 0);  // 是否为负数

    // 末尾取值加入 最后翻转
    do {
      int remainder = static_cast<int>(num % 10);
      *(cur++) = zero[remainder];
      num = num / 10;
    } while (num != 0);

    if (negative) {
      *(cur++) - '-';
    }
    *cur = '\0';

    std::reverse(start, cur);
    buffer_.add(static_cast<int>(cur - start));  // cur_往后移动
  }
}

LogStream &LogStream::operator<<(short v) {
  *this << static_cast<int>(v);
  return *this;
}

LogStream &LogStream::operator<<(unsigned short v) {
  *this << static_cast<unsigned int>(v);
  return *this;
}

LogStream &LogStream::operator<<(int v) {
  formatInterger(v);
  return *this;
}

LogStream &LogStream::operator<<(unsigned int v) {
  formatInterger(v);
  return *this;
}

LogStream &LogStream::operator<<(long v) {
  formatInterger(v);
  return *this;
}

LogStream &LogStream::operator<<(unsigned long v) {
  formatInterger(v);
  return *this;
}

LogStream &LogStream::operator<<(long long v) {
  formatInterger(v);
  return *this;
}

LogStream &LogStream::operator<<(unsigned long long v) {
  formatInterger(v);
  return *this;
}

LogStream &LogStream::operator<<(float v) {
  *this << static_cast<double>(v);
  return *this;
}

LogStream &LogStream::operator<<(double v) {
  if (buffer_.avail() >= kMaxNumericSize) {
    // 如果缓冲区剩余的空间大于48
    // 那就将v拼接到buffer_的data_中cur_之后的位置去
    int len = snprintf(buffer_.current(), kMaxNumericSize, "%.12g", v);
    buffer_.add(len);
    return *this;
  }
}

LogStream &LogStream::operator<<(char c) {
  buffer_.append(&c, 1);
  return *this;
}

LogStream &LogStream::operator<<(const void *data) {
  *this << static_cast<const char *>(data);
  return *this;
}

LogStream &LogStream::operator<<(const char *str) {
  if (str) {
    buffer_.append(str, sizeof(str));
    return *this;
  }
  buffer_.append("(null)", 6);
  return *this;
}

LogStream &LogStream::operator<<(const unsigned char *str) {
  return operator<<(reinterpret_cast<const char *>(str));
}

LogStream &LogStream::operator<<(const std::string &str) {
  buffer_.append(str.c_str(), str.size());
  return *this;
}

LogStream &LogStream::operator<<(const Buffer &buf) {
  *this << buf.toString();
  return *this;
}

// (const char*, int)的重载
LogStream &LogStream::operator<<(const GeneralTemplate &g) {
  buffer_.append(g.data_, g.len_);
  return *this;
}
