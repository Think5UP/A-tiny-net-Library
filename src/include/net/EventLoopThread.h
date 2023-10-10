#ifndef EVENTLOOPTHREAD_H_
#define EVENTLOOPTHREAD_H_

#include <condition_variable>
#include <functional>
#include <mutex>

#include "Channel.h"
#include "Thread.h"
#include "noncopyable.h"

class EventLoop;

class EventLoopThread : noncopyable {
 public:
  using ThreadInitCallback = std::function<void(EventLoop *)>;

  EventLoopThread(const ThreadInitCallback &cb = ThreadInitCallback(),
                  const std::string &name = std::string());
  ~EventLoopThread();

  EventLoop *startLoop();

 private:
  void threadFunc();

  EventLoop *loop_;
  bool exiting_;
  Thread thread_;
  std::mutex mutex_;
  std::condition_variable cond_;
  ThreadInitCallback callback_;
};

#endif  // !EVENTLOOPTHREAD_H_