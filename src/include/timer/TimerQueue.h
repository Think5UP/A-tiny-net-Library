#ifndef TIMERQUEUE_H_
#define TIMERQUEUE_H_

#include <set>
#include <vector>

#include "Channel.h"
#include "Timestamp.h"

class EventLoop;
class Timer;

class TimerQueue {
 public:
  using TimerCallBack = std::function<void()>;

  explicit TimerQueue(EventLoop *loop);
  ~TimerQueue();

  void addTimer(TimerCallBack cb, Timestamp when, double interval);

 private:
  using Entry = std::pair<Timestamp, Timer *>;
  using TimerList = std::set<Entry>;

  // 在本loop中添加定时器
  // 线程安全
  void addTimerInLoop(Timer *timer);

  // 定时器读事件触发的函数
  void handleRead();

  void resetTimerfd(int timerfd, Timestamp expiration);

  // 移除所有已到期的定时器
  // 1.获取到期的定时器
  // 2.重置这些定时器（销毁或者重复定时任务）
  std::vector<Entry> getExpired(Timestamp now);
  void reset(const std::vector<Entry> &expired, Timestamp now);

  bool insert(Timer *timer);

  EventLoop *loop_;         // 所属的EventLoop
  const int timerfd_;       // timerfd是Linux提供的定时器接口
  Channel timerfdChannel_;  // 封装timerfd_文件描述符
  TimerList timers_;        // 定时器队列（内部实现是红黑树）

  bool callingExpiredTimers_;  // 标明正在获取超时定时器
};

#endif  // !TIMERQUEUE_H_
