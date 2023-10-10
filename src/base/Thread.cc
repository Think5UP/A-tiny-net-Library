#include "Thread.h"

#include <semaphore.h>

#include "CurrentThread.h"

std::atomic_int32_t Thread::numCreated_(0);

Thread::Thread(ThreadFunc func, const std::string& name)
    : started_(false),
      joined_(false),
      tid_(0),
      func_(std::move(func)),
      name_(name) {
  setDefaultName();
}

Thread::~Thread() {
  // 线程开启并且没有等待
  if (started_ && !joined_) {
    // 线程分离
    thread_->detach();
  }
}

void Thread::start() {
  started_ = true;
  sem_t sem;
  sem_init(&sem, false, 0);

  thread_ = std::shared_ptr<std::thread>(new std::thread([&]() {
    // 初始化线程 获取tid
    tid_ = CurrentThread::tid();
    // 唤起主线程
    sem_post(&sem);

    // 执行回调
    func_();
  }));

  sem_wait(&sem);
}

void Thread::join() {
  joined_ = true;
  thread_->join();
}

void Thread::setDefaultName() {
  int num = ++numCreated_;
  if (name_.empty()) {
    char buf[32] = {0};
    snprintf(buf, sizeof(buf), "Thread%d", num);
    name_ = buf;
  }
}
