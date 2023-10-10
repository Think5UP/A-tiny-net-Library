#include "AsyncLogging.h"

#include <stdio.h>

#include "Timestamp.h"

AsyncLogging::AsyncLogging(const std::string& baseName, off_t rollSize,
                           int flushInterval)
    : flushInterval_(flushInterval),
      running_(false),
      baseName_(baseName),
      rollSize_(rollSize),
      thread_(std::bind(&AsyncLogging::threadFunc, this), "Logging"),
      mutex_(),
      cond_(),
      currentBuffer_(new Buffer),
      nextBuffer_(new Buffer),
      buffers_() {
  currentBuffer_->bzero();
  nextBuffer_->bzero();
  buffers_.reserve(16);
}

void AsyncLogging::append(const char* logline, int len) {
  std::lock_guard<std::mutex> lock(mutex_);
  // 当前缓冲区中剩下的空间足够 直接写
  if (currentBuffer_->avail() > len) {
    currentBuffer_->append(logline, len);
  } else {
    // 缓冲区的空间不够了 那就将信息存到buffers_中
    // 然后利用要么写入nextBuffer_缓冲区或者就将currentBuffer_原位构造一个
    buffers_.push_back(std::move(currentBuffer_));
    if (nextBuffer_) {
      currentBuffer_ = std::move(nextBuffer_);
    } else {
      currentBuffer_.reset(new Buffer);
    }
    currentBuffer_->append(logline, len);
    cond_.notify_one();
  }
}

void AsyncLogging::threadFunc() {
  LogFile output(baseName_, rollSize_);
  BufferPtr newBuffer1(new Buffer);
  BufferPtr newBuffer2(new Buffer);
  newBuffer1->bzero();
  newBuffer2->bzero();
  BufferVector buffersToWrite;
  buffersToWrite.reserve(16);
  while (running_) {
    {
      std::unique_lock<std::mutex> lock(mutex_);
      if (buffers_.empty()) {
        cond_.wait_for(lock, std::chrono::seconds(3));
      }
      // 将当前的缓冲区也放进bufffers中(没写完也放进去,避免等待太久才刷新一次)
      buffers_.push_back(std::move(currentBuffer_));
      currentBuffer_ = std::move(newBuffer1);
      // 后端缓冲区和前端缓冲区交换
      buffersToWrite.swap(buffers_);
      if (!nextBuffer_) {
        nextBuffer_ = std::move(newBuffer2);
      }
    }

    // 将后端缓冲区中的内容写入到文件中
    for (const auto& buffer : buffersToWrite) {
      output.append(buffer->data(), buffer->length());
    }

    // 将后端缓冲区重置为2
    if (buffersToWrite.size() > 2) {
      buffersToWrite.resize(2);
    }

    // 将newbuffer从后端缓冲区归还给前端缓冲区
    if (!newBuffer1) {
      newBuffer1 = std::move(buffersToWrite.back());
      buffersToWrite.pop_back();
      newBuffer1->reset();
    }

    if (!newBuffer2) {
      newBuffer2 = std::move(buffersToWrite.back());
      buffersToWrite.pop_back();
      newBuffer2->reset();
    }

    // 将后端缓冲区以及文件缓冲区清空
    buffersToWrite.clear();
    output.flush();
  }
  // 停止了那就直接刷新写给文件
  output.flush();
}
