#ifndef EVENTLOOP_H_
#define EVENTLOOP_H_

#include <atomic>
#include <functional>
#include <memory>
#include <mutex>
#include <vector>

#include "CurrentThread.h"
#include "TimerQueue.h"
#include "Timestamp.h"
#include "noncopyable.h"

class Channel;
class Poller;

class EventLoop : noncopyable {
 private:
  /* data */
 public:
  using Functor = std::function<void()>;

  EventLoop();
  ~EventLoop();

  void loop();
  void quit();

  Timestamp pollReturnTime() const { return pollReturnTime_; }

  void runInLoop(Functor cb);

  void queueInLoop(Functor cb);

  void wakeup();

  void updateChannel(Channel *);
  void removeChannel(Channel *);
  bool hasChannel(Channel *);

  bool isInLoopThread() { return threadId_ == CurrentThread::tid(); }

 private:
  void handleRead();         // wake up
  void doPendingFunctors();  // 执行回调函数

  std::atomic_bool looping_;
  std::atomic_bool quit_;                    // 表示是否退出
  std::atomic_bool callingPendingFunctors_;  // 当前loop是否需要执行回调的标志

  const pid_t threadId_;  // 当前loop所在的线程 用于比较loop是否在自己的线程中
  Timestamp pollReturnTime_;
  std::unique_ptr<Poller> poller_;

  int wakeupFd_;  // mainLoop向subloop::wakeupFd写数据唤醒
                  // 如果需要唤醒某个EventLoop执行异步操作，就向其wakeupFd_写入数据。
  std::unique_ptr<Channel> wakeupChannel_;
  std::unique_ptr<TimerQueue> timerQueue_;

  using ChannelList = std::vector<Channel *>;
  ChannelList activeChannels_;     // 存放活跃的Channel
  Channel *currentActiveChannel_;  // 当前正在处理的活跃的Channel

  std::mutex mutex_;  // 为了保护pendingFunctors_的线程安全
  // 存放loop跨线程需要执行的所有的回调操作
  // 如果涉及跨线程调用函数时，会将函数储存到pendingFunctors_这个任务队列中。
  std::vector<Functor> pendingFunctors_;
};

#endif  // !EVENTLOOP_H_