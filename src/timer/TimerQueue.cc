#include "TimerQueue.h"

#include <string.h>
#include <sys/timerfd.h>
#include <unistd.h>

#include "EventLoop.h"
#include "Logging.h"
#include "Timer.h"

int createTimerfd() {
  int timerfd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
  if (timerfd < 0) {
    LOG_ERROR << "createTimerfd error";
  }
  return timerfd;
}

TimerQueue::TimerQueue(EventLoop* loop)
    : loop_(loop),
      timerfd_(createTimerfd()),
      timerfdChannel_(loop_, timerfd_),
      timers_() {
  timerfdChannel_.setReadCallBack(std::bind(&TimerQueue::handleRead, this));
  timerfdChannel_.enableReadEvent();
}

TimerQueue::~TimerQueue() {
  timerfdChannel_.disAllEvent();
  timerfdChannel_.remove();
  ::close(timerfd_);
  for (const Entry& timer : timers_) {
    delete timer.second;
  }
}

void TimerQueue::addTimer(TimerCallBack cb, Timestamp when, double interval) {
  Timer* timer = new Timer(std::move(cb), when, interval);
  loop_->runInLoop(std::bind(&TimerQueue::addTimerInLoop, this, timer));
}

void TimerQueue::addTimerInLoop(Timer* timer) {
  bool eraliestChanged = insert(timer);
  if (eraliestChanged) {
    resetTimerfd(timerfd_, timer->expiration());
  }
}

void ReadTimerfd(int timerfd) {
  uint64_t readByte;
  ssize_t read = ::read(timerfd, &readByte, sizeof(readByte));
  // 如果读取的字节数不是8个字节说明出现了错误
  if (read != sizeof(readByte)) {
    LOG_ERROR << "ReadTimerfd: read != readByte ";
  }
}

void TimerQueue::handleRead() {
  Timestamp now = Timestamp::now();
  ReadTimerfd(timerfd_);

  std::vector<Entry> expired = getExpired(now);

  callingExpiredTimers_ = true;
  // 处理超时定时器
  for (const auto& it : expired) {
    it.second->run();
  }
  callingExpiredTimers_ = false;

  // 重新设置这些超时的定时器
  reset(expired, now);
}

void TimerQueue::resetTimerfd(int timerfd, Timestamp expiration) {
  /*
    表示 POSIX 定时器的时间设置。
    POSIX 定时器是一种用于定期触发信号或产生事件的机制
    struct itimerspec {
      struct timespec it_interval; // 定时器间隔
      struct timespec it_value;    // 初始定时器溢出之前的延迟时间
    };
    struct timespec {
        time_t tv_sec;  // 秒数
        long tv_nsec;   // 纳秒数
    };
   */
  struct itimerspec newValue;
  struct itimerspec oldValue;
  memset(&newValue, '\0', sizeof(newValue));
  memset(&oldValue, '\0', sizeof(oldValue));

  // 计算超时时间差
  int64_t microSecondDif = expiration.microSecondsSinceEpoch() -
                           Timestamp::now().microSecondsSinceEpoch();
  if (microSecondDif < 100) {
    // 确保定时器至少有100ms的最小超时时间
    microSecondDif = 100;
  }

  struct timespec ts;
  ts.tv_sec = static_cast<time_t>(
      (microSecondDif / Timestamp::kMicroSecondsPerSecond) * 1000);

  ts.tv_nsec = static_cast<long>(
      (microSecondDif % Timestamp::kMicroSecondsPerSecond) * 1000);
  newValue.it_value = ts;
  if (::timerfd_settime(timerfd_, 0, &newValue, &oldValue)) {
    LOG_ERROR << "timerfd_settime faield! ";
  }
}

// 获得删除的定时器
std::vector<TimerQueue::Entry> TimerQueue::getExpired(Timestamp now) {
  std::vector<TimerQueue::Entry> expired;
  TimerQueue::Entry sentry(now, reinterpret_cast<Timer*>(UINTPTR_MAX));
  TimerList::iterator end = timers_.lower_bound(sentry);
  std::copy(timers_.begin(), end, back_inserter(expired));
  timers_.erase(timers_.begin(), end);

  return expired;
}

void TimerQueue::reset(const std::vector<Entry>& expired, Timestamp now) {
  Timestamp nerExpire;
  for (const auto it : expired) {
    if (it.second->repeat()) {
      auto timer = it.second;
      timer->restart(Timestamp::now());
      insert(timer);
    } else {
      delete it.second;
    }

    // 如果重新插入了定时器，需要继续重置timerfd
    if (!timers_.empty()) {
      resetTimerfd(timerfd_, (timers_.begin()->second)->expiration());
    }
  }
}

bool TimerQueue::insert(Timer* timer) {
  bool earliestChanged = false;
  Timestamp when = timer->expiration();
  TimerList::iterator it = timers_.begin();
  if (it == timers_.end() || when < it->first) {
    // 说明最早的定时器已经被替换了
    earliestChanged = true;
  }

  // 定时器管理红黑树插入此新定时器
  timers_.insert(Entry(when, timer));

  return earliestChanged;
}
