#include "ThreadPool.h"

ThreadPool::ThreadPool(const std::string &name)
    : name_(name), running_(false) {}

ThreadPool::~ThreadPool() {
  stop();
  // 等待所有线程join
  for (const auto &it : threads_) {
    it->join();
  }
}

void ThreadPool::start() {
  running_ = true;
  threads_.reserve(threadSize_);
  for (int i = 0; i < threadSize_; ++i) {
    char id[32];
    snprintf(id, sizeof(id), "%d", i + 1);
    // 创建线程 然后将线程执行函数绑定给线程
    threads_.emplace_back(
        new Thread(std::bind(&ThreadPool::runInThread, this), name_ + id));
    threads_[i]->start();
  }
  // 如果threadSize_是0 导致没有创建线程 那就先调用线程初始化函数
  if (threadSize_ == 0 && threadInitCallback_) {
    threadInitCallback_();
  }
}

void ThreadPool::stop() {
  std::lock_guard<std::mutex> lock(mutex_);
  running_ = false;
  cond_.notify_all();  // 唤醒所有线程
}

size_t ThreadPool::queueSize() const {
  std::lock_guard<std::mutex> lock(mutex_);
  return queue_.size();
}

void ThreadPool::add(ThreadFunction cb) {
  std::unique_lock<std::mutex> lock(mutex_);
  queue_.push_back(cb);
  cond_.notify_one();
}

void ThreadPool::runInThread() {
  try {
    if (threadInitCallback_) {
      threadInitCallback_();
    }
    ThreadFunction task;
    while (running_) {
      {
        std::unique_lock<std::mutex> lock(mutex_);
        while (queue_.empty()) {
          if (!running_) {
            return;
          }
          cond_.wait(lock);
        }
        task = queue_.front();
        queue_.pop_front();
      }
      if (task != nullptr) {
        task();
      }
    }
  } catch (...) {
  }
}