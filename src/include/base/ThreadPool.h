#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include <condition_variable>
#include <deque>
#include <mutex>
#include <vector>

#include "Logging.h"
#include "Thread.h"
#include "noncopyable.h"

class ThreadPool : noncopyable {
 public:
  using ThreadFunction = std::function<void()>;

  explicit ThreadPool(const std::string &name = std::string("ThreadPool"));
  ~ThreadPool();

  void start();
  void stop();

  void setThreadInitCallback(const ThreadFunction &cb) {
    threadInitCallback_ = cb;
  }
  void setThreadSize(const int &num) { threadSize_ = num; }

  const std::string &name() const { return name_; }
  size_t queueSize() const;

  void add(ThreadFunction cb);

 private:
  bool isFull() const;
  void runInThread();

  mutable std::mutex mutex_;           // 互斥锁
  std::condition_variable cond_;       // 条件变量
  std::string name_;                   // 线程名称
  ThreadFunction threadInitCallback_;  // 线程初始化的回调函数
  std::vector<std::unique_ptr<Thread>> threads_;
  std::deque<ThreadFunction> queue_;
  bool running_;
  size_t threadSize_;
};

#endif  // !THREAD_POOL_H_