#include "EventLoopThreadPool.h"

#include <memory>

#include "EventLoop.h"
#include "EventLoopThread.h"

EventLoopThreadPool::EventLoopThreadPool(EventLoop *baseLoop,
                                         const std::string &name)
    : baseLoop_(baseLoop),
      name_(name),
      started_(false),
      numThreads_(0),
      next_(0) {}

EventLoopThreadPool::~EventLoopThreadPool() {}

void EventLoopThreadPool::start(const ThreadInitCallback &cb) {
  started_ = true;
  for (int i = 0; i < numThreads_; ++i) {
    char buf[name_.size() + 32];
    snprintf(buf, sizeof buf, "%s%d", name_.c_str(), i);
    auto loopThread = new EventLoopThread(cb, buf);
    // 将存有EventLoopThread对象的智能指针添加到threads_中管理
    threads_.push_back(std::unique_ptr<EventLoopThread>(loopThread));
    // 底层创建线程 绑定一个新的EventLoop 并返回该loop的地址
    loops_.push_back(loopThread->startLoop());

    // 只有baseLoop那就把所有工作都交给它
    if (numThreads_ == 0 && cb) {
      cb(baseLoop_);
    }
  }
}

// 如果工作在多线程中，baseLoop_(mainLoop)会默认以轮询的方式分配Channel给subLoop
EventLoop *EventLoopThreadPool::getNextLoop() {
  // 如果只设置一个线程
  // 也就是只有一个mainReactor 无subReactor
  // 那么轮询只有一个线程 getNextLoop()每次都返回当前的baseLoop_
  EventLoop *loop = baseLoop_;
  // 通过轮询获取下一个处理事件的loop
  // 如果没设置多线程数量，则不会进去，相当于直接返回baseLoop
  if (!loops_.empty()) {
    loop = loops_[next_];
    ++next_;
    // 轮询
    if (next_ >= loops_.size()) {
      next_ = 0;
    }
  }
  return loop;
}

std::vector<EventLoop *> EventLoopThreadPool::getAllLoops() {
  if (loops_.empty()) {
    return std::vector<EventLoop *>(1, baseLoop_);
  } else {
    return loops_;
  }
}
