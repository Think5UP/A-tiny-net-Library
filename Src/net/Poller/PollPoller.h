//
// Created by root on 2/21/23.
//

#ifndef NET_LIB_POLLPOLLER_H
#define NET_LIB_POLLPOLLER_H

#include "Poller.h"

namespace net_lib{
    class EventLoop;

    class PollPoller : public Poller{
    public:
        PollPoller(EventLoop* loop);

    };
}

#endif //NET_LIB_POLLPOLLER_H
