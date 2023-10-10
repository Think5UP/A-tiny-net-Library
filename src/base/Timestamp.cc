#include "Timestamp.h"

#include <inttypes.h>
#include <stdio.h>

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif

Timestamp Timestamp::now() {
  struct timeval tv;
  // 通过gettimeofday获取当前时间的秒和微秒
  // 对于x86_64系统来说，这是个虚拟系统调用vsyscall！所以，这里它不用发送中断！速度很快，成本低，调用一次的成本大概不到一微秒！
  gettimeofday(&tv, NULL);
  int64_t seconds = tv.tv_sec;

  return Timestamp(seconds * kMicroSecondsPerSecond + tv.tv_usec);
}

std::string Timestamp::ToString() const {
  char buf[32] = {0};
  int64_t seconds = microSecondsSinceEpoch_ / kMicroSecondsPerSecond;
  int64_t microseconds = microSecondsSinceEpoch_ % kMicroSecondsPerSecond;
  snprintf(buf, sizeof(buf), "%" PRId64 ".%06" PRId64 "", seconds,
           microseconds);
  return buf;
}

std::string Timestamp::toFormatString(bool showMicroseconds) const {
  char buf[64] = {0};
  time_t seconds =
      static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);

  tm *tm_time = localtime(&seconds);

  if (showMicroseconds) {
    int microseconds =
        static_cast<int>(microSecondsSinceEpoch_ % kMicroSecondsPerSecond);
    snprintf(buf, sizeof(buf), "%4d/%02d/%02d %02d:%02d:%02d.%06d",
             tm_time->tm_year + 1900, tm_time->tm_mon + 1, tm_time->tm_mday,
             tm_time->tm_hour, tm_time->tm_min, tm_time->tm_sec, microseconds);
    return buf;
  }

  snprintf(buf, sizeof(buf), "%4d/%02d/%02d %02d:%02d:%02d",
           tm_time->tm_year + 1900, tm_time->tm_mon + 1, tm_time->tm_mday,
           tm_time->tm_hour, tm_time->tm_min, tm_time->tm_sec);
  return buf;
}
