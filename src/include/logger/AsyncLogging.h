#ifndef ASYNCLOGGING_H_
#define ASYNCLOGGING_H_

#include <condition_variable>
#include <memory>
#include <mutex>
#include <vector>

#include "FixedBuffer.h"
#include "LogFile.h"
#include "LogStream.h"
#include "Thread.h"
#include "noncopyable.h"

class AsyncLogging {
 public:
  AsyncLogging(const std::string &baseName, off_t rollSize,
               int flushInterval = 3);

  ~AsyncLogging() {
    if (running_) {
      stop();
    }
  }

  void append(const char *logline, int len);

  void start() {
    running_ = true;
    thread_.start();
  }

  void stop() {
    running_ = false;
    cond_.notify_one();
    thread_.join();
  }

 private:
  using Buffer = detail::FixedBuffer<detail::kLargeBuffer>;
  using BufferVector = std::vector<std::unique_ptr<Buffer>>;
  using BufferPtr = BufferVector::value_type;

  void threadFunc();

  const int flushInterval_;
  std::atomic<bool> running_;
  const std::string baseName_;
  const off_t rollSize_;
  Thread thread_;
  std::mutex mutex_;
  std::condition_variable cond_;

  BufferPtr currentBuffer_;
  BufferPtr nextBuffer_;
  BufferVector buffers_;
};

#endif  // !ASYNCLOGGING_H_
