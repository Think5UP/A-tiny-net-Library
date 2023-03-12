//
// Created by root on 23-2-14.
//

#ifndef NET_LIB_BASE_INCLUDE_DATE_H_
#define NET_LIB_BASE_INCLUDE_DATE_H_

#include "copyable.h"
#include "Types.h"

struct tm;
namespace net_lib {
class Date : public copyable {
 public:
  struct YearMonthDay {
    int year;
    int month;
    int day;
  };

  static const int kDayPerWeek = 7;
  static const int JulianDayOf1970_01_01;

  //无效构造，JulianDay构造,年月日构造
  Date() : julianDayNumber_(0) {}
  Date(int JulianDayNum) : julianDayNumber_(JulianDayNum) {}
  explicit Date(int year, int month, int day);
  explicit Date(const struct tm &);

  void swap(Date &dt) {
    std::swap(dt.julianDayNumber_, julianDayNumber_);
  }

  bool valid() const {
    return julianDayNumber_ > 0;
  }

  std::string toIsoString() const;

  struct YearMonthDay year_month_day_() const;

  int year() const {
    return year_month_day_().year;
  }

  int month() const {
    return year_month_day_().month;
  }

  int day() const {
    return year_month_day_().day;
  }

  //求出星期
  int weekDay() {
    return (julianDayNumber_ + 1) % kDayPerWeek;
  }

  int julianDayNumber() const { return julianDayNumber_; }

 private:
  int julianDayNumber_;
};

inline bool operator<(const Date &lhs, const Date &rhs) {
  return lhs.julianDayNumber() < rhs.julianDayNumber();
}

inline bool operator==(const Date &lhs, const Date &rhs) {
  return lhs.julianDayNumber() < rhs.julianDayNumber();
}
}
#endif //NET_LIB_BASE_INCLUDE_DATE_H_
