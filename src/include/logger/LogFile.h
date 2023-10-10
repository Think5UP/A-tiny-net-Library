#ifndef LOGFILE_H_
#define LOGFILE_H_

#include <memory>
#include <mutex>

#include "FileUtil.h"

class LogFile {
 public:
  LogFile(const std::string &baseName, off_t rollSize, int flushInterval = 3,
          int checkEveryN = 1024);

  ~LogFile() = default;

  void append(const char *data, int len);
  void flush();
  bool rollFile();

 private:
  static std::string getLogFileName(const std::string &baseName, time_t *now);
  void appendInLock(const char *data, int len);

  const std::string baseName_;
  const off_t rollSize_;
  const int flushInterval_;
  const int checkEveryN_;

  int count_;

  std::unique_ptr<std::mutex> mutex_;
  time_t startOfPeriod_;
  time_t lastRoll_;
  time_t lastFlush_;
  std::unique_ptr<FileUtil> file_;

  const static int kRollPerSeconds_ = 60 * 60 * 24;
};

#endif  // !LOGFILE_H_
