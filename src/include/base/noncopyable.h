#ifndef NONCOPYABLE_H_
#define NONCOPYABLE_H_

class noncopyable {
 public:
  noncopyable(const noncopyable &) = delete;
  noncopyable &operator=(const noncopyable &) = delete;

 protected:
  noncopyable() = default;
  ~noncopyable() = default;
};
#endif  // !NONCOPYABLE_H_
