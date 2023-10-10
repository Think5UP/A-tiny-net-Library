#ifndef EVENTLOOPTHREADPOOL_H_
#define EVENTLOOPTHREADPOOL_H_

#include <functional>
#include <memory>
#include <string>
#include <vector>

class EventLoop;
class EventLoopThread;

class EventLoopThreadPool {
 public:
  using ThreadInitCallback = std::function<void(EventLoop *)>;
  EventLoopThreadPool(EventLoop *baseLoop, const std::string &nameArg);
  ~EventLoopThreadPool();

  // 设置线程数量
  void setThreadNum(int numThreads) { numThreads_ = numThreads; }

  // 启动线程池
  void start(const ThreadInitCallback &cb = ThreadInitCallback());

  // 如果工作在多线程中，baseLoop_(mainLoop)会默认以轮询的方式分配Channel给subLoop
  EventLoop *getNextLoop();

  std::vector<EventLoop *> getAllLoops();

  bool started() const { return started_; }
  const std::string name() const { return name_; }

 private:
  // mainLoop如果numThreads_ = 1那就只会创建这一个
  // 然后所有的过程都在这个线程里进行
  EventLoop *baseLoop_;
  std::string name_;
  bool started_;    // 开启的标志
  int numThreads_;  // 线程数量
  size_t next_;     // 轮询的下标
  std::vector<std::unique_ptr<EventLoopThread>> threads_;
  std::vector<EventLoop *> loops_;
};

#endif  // !EVENTLOOPTHREADPOOL_H_