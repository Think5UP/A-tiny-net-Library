#include "LogFile.h"

LogFile::LogFile(const std::string& baseName, off_t rollSize, int flushInterval,
                 int checkEveryN)
    : baseName_(baseName),
      rollSize_(rollSize),
      flushInterval_(flushInterval),
      checkEveryN_(checkEveryN),
      count_(0),
      mutex_(new std::mutex),
      startOfPeriod_(0),
      lastRoll_(0),
      lastFlush_(0) {
  rollFile();
}

void LogFile::append(const char* data, int len) {
  // 上把大锁
  std::lock_guard<std::mutex> lock(*mutex_);
  appendInLock(data, len);
}

// 向日志文件中添加日志数据，在特定条件下进行日志文件的滚动（创建新的文件）或刷新文件内容到磁盘
void LogFile::appendInLock(const char* data, int len) {
  file_->append(data, len);

  // 检查写入量 大于rollSize滚动日志
  if (file_->writtenBytes() > rollSize_) {
    rollFile();
  } else {
    // 达不到但是追加次数到达了N次也考虑滚动日志
    ++count_;
    if (count_ >= checkEveryN_) {
      count_ = 0;
      time_t now = ::time(NULL);
      time_t thisPeriod = now / kRollPerSeconds_ * kRollPerSeconds_;
      // 如果当前时间段和上次记录的时间不同也满足滚动条件
      if (thisPeriod != startOfPeriod_) {
        rollFile();
      } else if (now - lastFlush_ > flushInterval_) {
        // 或者当前时间和上次刷新时间间隔大于flushInterval_就刷新日志
        lastFlush_ = now;
        file_->flush();
      }
    }
  }
}

void LogFile::flush() { file_->flush(); }

// 滚动日志
bool LogFile::rollFile() {
  time_t now = 0;
  std::string filename = getLogFileName(baseName_, &now);

  // 得到当前时间所在时间段的起始时间
  time_t start = now / kRollPerSeconds_ * kRollPerSeconds_;

  // 当前时间已经超过了上次滚动日志文件的时间 roll它
  if (now > lastRoll_) {
    lastRoll_ = now;
    lastFlush_ = now;
    startOfPeriod_ = start;
    file_.reset(new FileUtil(filename));
    return true;
  }
  return false;
}

// 将文件名称封装成basename + time + ".log"这样类型
std::string LogFile::getLogFileName(const std::string& baseName, time_t* now) {
  std::string filename;
  filename.reserve(baseName.size() + 64);
  filename = baseName;

  char timebuf[32];
  struct tm tm;
  *now = time(NULL);
  // 将当前时间戳转化为本地时间
  localtime_r(now, &tm);

  strftime(timebuf, sizeof(timebuf), ".%Y%m%d-%H%M%S", &tm);
  filename += timebuf;
  filename += ".log";

  return filename;
}
