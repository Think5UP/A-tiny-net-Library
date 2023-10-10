#ifndef TIMESTAMP_H_
#define TIMESTAMP_H_

#include <sys/time.h>

#include <iostream>
#include <string>

class Timestamp {
 public:
  Timestamp() : microSecondsSinceEpoch_(0) {}

  explicit Timestamp(int64_t microSecondsSinceEpoch)
      : microSecondsSinceEpoch_(microSecondsSinceEpoch) {}

  // 获取当前时间戳
  static Timestamp now();

  // 用std::string形式返回,格式[millisec].[microsec]
  std::string ToString() const;

  // 格式化打印时间 showMicroseconds是一个是否展示微秒的标志
  // "%4d年%02d月%02d日 星期%d %02d:%02d:%02d.%06d",时分秒.微秒
  std::string toFormatString(bool showMicroseconds = false) const;

  int64_t microSecondsSinceEpoch() const { return microSecondsSinceEpoch_; }

  time_t secondsSinceEpoch() const {
    return static_cast<time_t>(microSecondsSinceEpoch_ /
                               kMicroSecondsPerSecond);
  }

  static Timestamp invalid() { return Timestamp(); }

  // 方便微秒转化成秒的成员 1秒=1000*1000微秒
  static const int kMicroSecondsPerSecond = 1000 * 1000;

 private:
  // 时间戳的微秒数 从epoch开始计算
  int64_t microSecondsSinceEpoch_;
};

inline bool operator<(Timestamp lhs, Timestamp rhs) {
  return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
}

inline bool operator==(Timestamp lhs, Timestamp rhs) {
  return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
}

inline Timestamp addTime(Timestamp timestamp, double seconds) {
  int64_t delta =
      static_cast<int64_t>(seconds * Timestamp::kMicroSecondsPerSecond);
  return Timestamp(timestamp.microSecondsSinceEpoch() + delta);
}
#endif