#ifndef POLLER_H_
#define POLLER_H_

#include <unordered_map>
#include <vector>

#include "Channel.h"
#include "Timestamp.h"
#include "noncopyable.h"

class Poller : noncopyable {
 public:
  using ChannelList = std::vector<Channel *>;

  Poller(EventLoop *Loop);
  virtual ~Poller() = default;

  virtual Timestamp poll(int timeoutMs, ChannelList *activeChannels) = 0;
  virtual void updataChannel(Channel *channel) = 0;
  virtual void removeChannel(Channel *channel) = 0;

  bool hasChannel(Channel *channel) const;

  static Poller *newDefaultPoller(EventLoop *Loop);

 protected:
  using ChannelMap = std::unordered_map<int, Channel *>;
  ChannelMap channels_;

 private:
  EventLoop *ownerLoop_;
};

#endif  // !POLLER_H_