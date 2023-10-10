#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <sys/epoll.h>

#include <functional>
#include <memory>

#include "Logging.h"
#include "Timestamp.h"
#include "noncopyable.h"

class EventLoop;
class Timestamp;

class Channel : noncopyable {
 public:
  using EventCallBack = std::function<void()>;
  using ReadEventCallBack = std::function<void(Timestamp)>;

  Channel(EventLoop *loop, int fd);
  ~Channel();

  // 处理事件的回调函数
  void handleEvent(Timestamp receiveTime);

  void setReadCallBack(ReadEventCallBack cb) {
    readEventCallBack_ = std::move(cb);
  }

  void setWriteCallBack(EventCallBack cb) {
    writeEventCallBack_ = std::move(cb);
  }

  void setCloseCallBack(EventCallBack cb) {
    closeEventCallBack_ = std::move(cb);
  }

  void setErrorCallBack(EventCallBack cb) {
    errorEventCallBack_ = std::move(cb);
  }

  void tie(const std::shared_ptr<void> &obj);

  void setrEvents(int revent) { revents_ = revent; }

  int fd() const { return fd_; }
  int events() const { return events_; }

  // 设置读事件到Poller中
  void enableReadEvent() {
    events_ |= kReadEvent;
    update();
  }
  // 在Poller中关闭读事件
  void disableReadEvent() {
    events_ &= ~kReadEvent;
    update();
  }
  // 设置写事件到Poller中
  void enableWriteEvent() {
    events_ |= kWriteEvent;
    update();
  }
  // 在Poller中关闭写事件
  void disableWriteEvent() {
    events_ &= ~kWriteEvent;
    update();
  }
  // 在Poller关闭所有的事件
  void disAllEvent() {
    events_ = kNoneEvent;
    update();
  }
  // 读事件是否关注
  bool isReading() const { return events_ & kReadEvent; }
  // 写事件是否关注
  bool isWriting() const { return events_ & kWriteEvent; }
  // 是否不关注任何事件
  bool isNoneEvent() const { return events_ & kNoneEvent; }

  int index() const { return index_; }
  void setIndex(int index) { index_ = index; }

  EventLoop *ownerLoop() const { return loop_; }
  void remove();

 private:
  void update();
  void handleEventWithGuard(Timestamp receiveTime);

  static const int kNoneEvent;   // 不对任何事件感兴趣
  static const int kReadEvent;   // 对读事件感兴趣
  static const int kWriteEvent;  // 对写事件感兴趣

  EventLoop *loop_;  // 事件循环
  const int fd_;     // 监听的文件描述符
  int events_;       // 感兴趣的事件
  int revents_;      // 返回的发生的事件
  int index_;        // 在Poller中注册的情况

  // 指向TCPConnection(在必要可以时提升为强智能指针去增加引用计数防止Channel被误删)
  std::weak_ptr<void> tie_;
  bool tied_;

  // 从rEvent知道最终发生的事件，并且由这个事件来执行相应的回调函数.
  ReadEventCallBack readEventCallBack_;
  EventCallBack writeEventCallBack_;
  EventCallBack closeEventCallBack_;
  EventCallBack errorEventCallBack_;
};

#endif  // !CHANNEL_H_
