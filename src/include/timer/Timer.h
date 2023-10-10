#ifndef TIMER_H_
#define TIMER_H_

#include <functional>

#include "Timestamp.h"
#include "noncopyable.h"

class Timer : noncopyable {
 public:
  using TimerCallBack = std::function<void()>;

  Timer(TimerCallBack cb, Timestamp when, double interval)
      : callback_(cb),
        expiration_(when),
        interval_(interval),
        repeat_(interval > 0.0) {}

  void run() const { callback_(); }

  // 获取超时时刻
  Timestamp expiration() const { return expiration_; }

  // 是否重复使用
  bool repeat() const { return repeat_; }

  void restart(Timestamp now);

 private:
  const TimerCallBack callback_;
  Timestamp expiration_;   // 下一次超时时刻
  const double interval_;  // 超时事件间隔 如果是一次性定时器为0
  const bool repeat_;      // 标记是否是重复使用的定时器
};

#endif  // !TIMER_H_