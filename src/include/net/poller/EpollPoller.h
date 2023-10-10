#ifndef EPOLLPOLLER_H_
#define EPOLLPOLLER_H_

#include <sys/epoll.h>
#include <unistd.h>

#include <vector>

#include "Logging.h"
#include "Timestamp.h"
#include "poller.h"

class EPOllPoller : public Poller {
 public:
  using EventList = std::vector<epoll_event>;

  EPOllPoller(EventLoop *Loop);
  ~EPOllPoller() override;

  Timestamp poll(int timeoutMs, ChannelList *activeChannels) override;
  void updataChannel(Channel *channel) override;
  void removeChannel(Channel *channel) override;

 private:
  static const int kInitEventListSize = 16;

  void fillActiveChannels(int numEvents, ChannelList *activeChannels) const;

  void update(int operation, Channel *channel);

  int epollfd_;
  EventList events_;
};

#endif  // !EPOLLPOLLER_H_