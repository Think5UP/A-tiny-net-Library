//
// Created by root on 2/21/23.
//

#include <cstdlib>

#include "Poller/Poller.h"
#include "Poller/PollPoller.h"
#include "Poller/EpollPoller.h"

namespace net_lib{
    Poller *Poller::newDefaultPoller(EventLoop *loop) {
        if(::getenv("MUDUO_USE_POLL")){
            return nullptr;
        } else {
            return new EpollPoller(loop);
        }
    }
}
