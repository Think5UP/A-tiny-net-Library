#include "EpollPoller.h"

#include <string.h>

#include <cassert>

// 某个Channel还未添加至Poller
const int kNew = -1;  // Channel中的index_初始化为-1就是为了表示Channel的状态
// 某个Channel已经添加到Poller
const int kAdded = 1;
// 某个Channel已经被Poller删除
const int kDeleted = 2;

EPOllPoller::EPOllPoller(EventLoop* Loop)
    : Poller(Loop),
      epollfd_(::epoll_create1(EPOLL_CLOEXEC)),
      events_(kInitEventListSize) {
  if (epollfd_ < 0) {
    LOG_FATAL << "epoll_create() error: " << errno;
  }
}

EPOllPoller::~EPOllPoller() { ::close(epollfd_); }

// 通过epoll_wait获取活跃的channel,然后填充EventLoop的ChannelList,这样能保证一定是活跃的channel被回调函数处理
Timestamp EPOllPoller::poll(int timeoutMs, ChannelList* activeChannels) {
  size_t numEvents = ::epoll_wait(epollfd_, &(*events_.begin()),
                                  static_cast<int>(events_.size()), timeoutMs);
  // 防止切换线程时errno改变，所以需要将errno存储
  int savedErrno = errno;
  Timestamp now(Timestamp::now());
  // epoll监听到事件发生
  if (numEvents > 0) {
    fillActiveChannels(numEvents, activeChannels);
    if (numEvents == events_.size()) {
      events_.resize(events_.size() * 2);
    }
  } else if (numEvents == 0) {  // 超时
    LOG_DEBUG << "timeout!";
  } else {
    // 排除是因为中断导致的错误
    if (savedErrno != EINTR) {
      errno = savedErrno;
      LOG_ERROR << "EPOllPoller::poll() failed ";
    }
  }
  return now;
}

void EPOllPoller::updataChannel(Channel* channel) {
  const int index = channel->index();
  // 获取Channel的状态
  if (index == kNew || index == kDeleted) {
    int fd = channel->fd();
    if (index == kNew) {
      channels_[fd] = channel;
    } else {
      // 某个已经被标记删除但是还在channels_的channel关心事件改变中的话
      // 重新更改它的状态
      assert(channels_.find(fd) != channels_.end());
      assert(channels_[fd] == channel);
    }
    channel->setIndex(kAdded);
    update(EPOLL_CTL_ADD, channel);
  } else {
    // 已经不关心任何事件 标记这个channel为kDeleted 反之只是修改关心的事件
    if (channel->isNoneEvent()) {
      update(EPOLL_CTL_DEL, channel);
      channel->setIndex(kDeleted);
    } else {
      update(EPOLL_CTL_MOD, channel);
    }
  }
}

void EPOllPoller::removeChannel(Channel* channel) {
  int fd = channel->fd();
  channels_.erase(fd);
  int index = channel->index();

  /*确认channel已经在ChannelMap中注册过能够找到
   *同时index为kAdded|kDeleted，并且channel已经没有关注的事件
   *那就将channel从ChannelMap中删除
   *如果index==kAdded那就还需要将channel从epoll中删除
   */
  assert(channels_.find(fd) != channels_.end());
  assert(channels_[fd] == channel);
  assert(channel->isNoneEvent());
  assert(index == kAdded || index == kDeleted);
  if (index == kAdded) {
    update(EPOLL_CTL_DEL, channel);
  }
  channel->setIndex(kNew);
}

// 将发生事件的channel添加到activeChannels中
void EPOllPoller::fillActiveChannels(int numEvents,
                                     ChannelList* activeChannels) const {
  for (int i = 0; i < numEvents; ++i) {
    // void* => Channel*
    Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
    channel->setrEvents(events_[i].events);
    activeChannels->push_back(channel);
  }
}

void EPOllPoller::update(int operation, Channel* channel) {
  int fd = channel->fd();
  struct epoll_event event;
  ::memset(&event, 0, sizeof(event));

  event.events = channel->events();
  event.data.fd = fd;
  event.data.ptr = channel;

  if (::epoll_ctl(epollfd_, operation, fd, &event) < 0) {
    if (operation == EPOLL_CTL_DEL) {
      LOG_ERROR << "epoll_ctl() del error: " << errno;
    } else {
      LOG_FATAL << "epoll_ctl add/mod error: " << errno;
    }
  }
}
