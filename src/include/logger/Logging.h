#ifndef LOGGING_H_
#define LOGGING_H_

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include <functional>
#include <iostream>

#include "LogStream.h"
#include "Timestamp.h"

class SourceFile {
 public:
  template <int N>
  SourceFile(const char (&arr)[N]) : data_(arr), size_(N - 1) {
    // 从data中找到最后一次/出现的位置 然后获取文件名
    const char *slash = strrchr(data_, '/');
    if (slash) {
      data_ = slash + 1;
      size_ -= static_cast<int>(data_ - arr);
    }
  }

  explicit SourceFile(const char *filename) : data_(filename) {
    const char *slash = strrchr(filename, '/');
    if (slash) {
      data_ = slash + 1;
    } else {
    }
    size_ = static_cast<int>(strlen(data_));
  }

  const char *data_;
  int size_;
};

class Logger {
 public:
  enum LogLevel {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
    LEVEL_COUNT,
  };
  Logger(const char *file, int line);
  Logger(const char *file, int line, LogLevel level);
  Logger(const char *file, int line, LogLevel level, const char *func);
  ~Logger();

  LogStream &stream() { return impl_.stream_; }

  static LogLevel logLevel();
  static void setLogLevel(LogLevel level);

  // 输出以及刷新缓冲区
  using OutputFunc = std::function<void(const char *msg, int len)>;
  using FlushFunc = std::function<void()>;
  static void setOutput(OutputFunc);
  static void setFlush(FlushFunc);

 private:
  class Impl {
   public:
    using LogLevel = Logger::LogLevel;
    Impl(LogLevel level, int savedErrno, const char *file, int line);
    void formatTime();
    void finish();

    Timestamp time_;
    LogStream stream_;
    LogLevel level_;
    int line_;
    SourceFile baseName_;
  };

  Impl impl_;
};

extern Logger::LogLevel g_logLevel;

inline Logger::LogLevel logLevel() { return g_logLevel; }

// 获取错误号相关信息
const char *getErrnoMsg(int savedErrno);

/**
 * 当日志等级小于对应等级才会输出
 * 比如设置等级为FATAL，则logLevel等级大于DEBUG和INFO，DEBUG和INFO等级的日志就不会输出
 */
#define LOG_DEBUG                  \
  if (logLevel() <= Logger::DEBUG) \
  Logger(__FILE__, __LINE__, Logger::DEBUG, __func__).stream()
#define LOG_INFO \
  if (logLevel() <= Logger::INFO) Logger(__FILE__, __LINE__).stream()
#define LOG_WARN Logger(__FILE__, __LINE__, Logger::WARN).stream()
#define LOG_ERROR Logger(__FILE__, __LINE__, Logger::ERROR).stream()
#define LOG_FATAL Logger(__FILE__, __LINE__, Logger::FATAL).stream()

#endif  // !LOGGING_H_