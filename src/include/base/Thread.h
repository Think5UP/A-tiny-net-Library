#ifndef THREAD_H_
#define THREAD_H_

#include <atomic>
#include <functional>
#include <memory>
#include <string>
#include <thread>

#include "noncopyable.h"

class Thread : noncopyable {
 public:
  using ThreadFunc = std::function<void()>;
  explicit Thread(ThreadFunc func, const std::string &name = std::string());
  ~Thread();

  void start();
  void join();

  bool started() const { return started_; }
  pid_t tid() const { return tid_; }
  const std::string &name() const { return name_; }
  static int numCreated() { return numCreated_; }

 private:
  void setDefaultName();  // 默认线程名
  bool started_;          // 线程启动的标志
  bool joined_;           // 线程等待的标志
  pid_t tid_;             // 线程tid
  std::shared_ptr<std::thread> thread_;

  // Thread::start() 调用的回调函数
  // 其实保存的是 EventLoopThread::threadFunc()
  ThreadFunc func_;                        // 线程回调函数
  std::string name_;                       // 线程名
  static std::atomic_int32_t numCreated_;  // 线程索引
};

#endif  // !THREAD_H_