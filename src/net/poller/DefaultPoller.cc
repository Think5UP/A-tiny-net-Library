#include <stdlib.h>

#include <cstddef>

#include "EpollPoller.h"
#include "poller.h"

Poller *Poller::newDefaultPoller(EventLoop *Loop) {
  if (::getenv("USE_POLL")) {
    return nullptr;
  }
  return new EPOllPoller(Loop);
}