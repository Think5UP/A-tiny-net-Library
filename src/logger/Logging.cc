#include "Logging.h"

#include "CurrentThread.h"

namespace ThreadInfo {
__thread char t_errnobuf[512];
__thread char t_time[64];
__thread time_t t_lastSecond;
}  // namespace ThreadInfo

const char *getErrnoMsg(int savedErrno) {
  return strerror_r(savedErrno, ThreadInfo::t_errnobuf,
                    sizeof(ThreadInfo::t_errnobuf));
}

const char *getLevelName[Logger::LogLevel::LEVEL_COUNT]{
    "[TRACE] ", "[DEBUG] ", "[INFO] ", "[WARN] ", "[ERROR] ", "[FATAL] ",
};

Logger::LogLevel initLogLevel() { return Logger::INFO; }

Logger::LogLevel g_logLevel = initLogLevel();

// 默认写入到终端中
static void defaultOutPut(const char *data, int len) {
  fwrite(data, len, sizeof(char), stdout);
}

// 默认将日志输出到终端中 需要刷新一下缓冲区的内容才能保证正确的日志信息输出
static void defaultFlush() { fflush(stdout); }

Logger::OutputFunc g_output = defaultOutPut;
Logger::FlushFunc g_flush = defaultFlush;

Logger::Impl::Impl(Logger::LogLevel level, int savedErrno, const char *file,
                   int line)
    : time_(Timestamp::now()),
      stream_(),
      level_(level),
      line_(line),
      baseName_(file) {
  formatTime();
  // 向流中写入日志等级
  stream_ << GeneralTemplate(getLevelName[level], 8);

  if (savedErrno != 0) {
    stream_ << getErrnoMsg(savedErrno) << " (errno= " << savedErrno << ") ";
  }
}

void Logger::Impl::formatTime() {
  Timestamp now = Timestamp::now();

  time_t seconds = static_cast<time_t>(now.microSecondsSinceEpoch() /
                                       now.kMicroSecondsPerSecond);
  int microSeconds = static_cast<int>(now.microSecondsSinceEpoch() %
                                      Timestamp::kMicroSecondsPerSecond);

  struct tm *tm_time = localtime(&seconds);
  // 写入此线程存储的时间buf中
  snprintf(ThreadInfo::t_time, sizeof(ThreadInfo::t_time),
           "%4d/%02d/%02d %02d:%02d:%02d", tm_time->tm_year + 1900,
           tm_time->tm_mon + 1, tm_time->tm_mday, tm_time->tm_hour,
           tm_time->tm_min, tm_time->tm_sec);
  // 更新最后一次时间调用
  ThreadInfo::t_lastSecond = seconds;

  // muduo使用Fmt格式化整数，这里我们直接写入buf
  char buf[32] = {0};
  snprintf(buf, sizeof(buf), "%06d ", microSeconds);

  // 输出时间，附有微妙(之前是(buf, 6),少了一个空格)
  stream_ << GeneralTemplate(ThreadInfo::t_time, 17) << GeneralTemplate(buf, 7);
}

void Logger::Impl::finish() {
  stream_ << " - " << GeneralTemplate(baseName_.data_, baseName_.size_) << ':'
          << line_ << '\n';
}

Logger::Logger(const char *file, int line) : impl_(INFO, 0, file, line) {}

Logger::Logger(const char *file, int line, Logger::LogLevel level)
    : impl_(level, 0, file, line) {}

Logger::Logger(const char *file, int line, Logger::LogLevel level,
               const char *func)
    : impl_(level, 0, file, line) {
  impl_.stream_ << func << ' ';
}

Logger::~Logger() {
  impl_.finish();
  // 从steam_中获取buf 构造一个对象
  const LogStream::Buffer &buf(stream().buffer());
  // 输出buf中的数据
  g_output(buf.data(), buf.length());
  // 如果日志等级为FATAL直接中止程序
  if (impl_.level_ == FATAL) {
    g_flush();
    // 立即终止当前进程，产生异常程序终止
    // 进程终止时不会销毁任何对象
    abort();
  }
}

// LogLevel Logger::logLevel() { return LogLevel(); }

void Logger::setLogLevel(Logger::LogLevel level) { g_logLevel = level; }

void Logger::setOutput(OutputFunc out) { g_output = out; }

void Logger::setFlush(FlushFunc flush) { g_flush = flush; }
