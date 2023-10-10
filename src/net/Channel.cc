#include "Channel.h"

#include "EventLoop.h"

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = EPOLLIN | EPOLLPRI;
const int Channel::kWriteEvent = EPOLLOUT;

Channel::Channel(EventLoop* loop, int fd)
    : loop_(loop), fd_(fd), events_(0), revents_(0), index_(-1), tied_(false) {}

Channel::~Channel() {}

void Channel::handleEvent(Timestamp receiveTime) {
  if (tied_) {
    std::shared_ptr<void> guard = tie_.lock();
    if (guard) {
      handleEventWithGuard(receiveTime);
    }
  } else {
    handleEventWithGuard(receiveTime);
  }
}

void Channel::tie(const std::shared_ptr<void>& obj) {
  tie_ = obj;
  tied_ = true;
}

void Channel::remove() { loop_->removeChannel(this); }

void Channel::update() { loop_->updateChannel(this); }

void Channel::handleEventWithGuard(Timestamp receiveTime) {
  // 对端关闭连接
  if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN)) {
    if (closeEventCallBack_) {
      closeEventCallBack_();
    }
  }
  // 发生错误
  if (revents_ & EPOLLERR) {
    LOG_ERROR << "the fd = " << this->fd();
    if (errorEventCallBack_) {
      errorEventCallBack_();
    }
  }
  // 对端发来信息
  if (revents_ & (EPOLLIN | EPOLLPRI)) {
    if (readEventCallBack_) {
      readEventCallBack_(receiveTime);
    }
  }
  // 发送给对端
  if (revents_ & EPOLLOUT) {
    LOG_DEBUG << "channel have read events, the fd = " << this->fd();
    if (writeEventCallBack_) {
      LOG_DEBUG << "channel call the readCallback_(), the fd = " << this->fd();
      writeEventCallBack_();
    }
  }
}
