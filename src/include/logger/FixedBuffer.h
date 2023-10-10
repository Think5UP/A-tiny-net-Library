#ifndef FIXED_BUFFER_H_
#define FIXED_BUFFER_H_

#include <assert.h>
#include <string.h>  // for memcpy
#include <strings.h>

#include <iostream>
#include <string>

#include "noncopyable.h"

namespace detail {
// 针对不同缓冲区设置不同的容量
const int kSmallBuffer = 4000;         // 4K
const int kLargeBuffer = 4000 * 1000;  // 4M

template <int SIZE>
class FixedBuffer : noncopyable {
 public:
  FixedBuffer() : cur_(data_) {}

  // 查看当前data_剩下的位置能不能追加上buf长度的缓冲区 可以就追加
  // 然后将cur_设置到追加完之后的位置
  void append(const char *buf, size_t len) {
    // 缓冲区中还能够容纳len直接加上
    if (static_cast<size_t>(avail()) > len) {
      memcpy(cur_, buf, len);
      cur_ += len;
    }
  }

  const char *data() const { return data_; }
  int length() const { return static_cast<int>(end() - data_); }

  char *current() const { return cur_; }
  // 获取data_剩下的大小
  int avail() const { return static_cast<int>(end() - cur_); }
  void add(size_t len) { cur_ += len; }

  void reset() { cur_ = data_; }
  void bzero() { ::bzero(data_, sizeof(data_)); }

  std::string toString() const { return std::string(data_, length()); }

 private:
  // 返回指向data_末尾的指针
  const char *end() const { return data_ + sizeof(data_); };

  char data_[SIZE];
  // 指向已经使用到的位置的指针
  char *cur_;
};
}  // namespace detail

#endif  // !