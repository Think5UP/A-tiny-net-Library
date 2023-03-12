//
// Created by root on 2/21/23.
//

#include "Poller.h"
#include "../Channel.h"

namespace net_lib{

    Poller::Poller(EventLoop *loop) : ownerLoop_(loop){}

    Poller::~Poller() = default;


    bool Poller::hasChannel(Channel *channel) const {
        auto it = Channels_.find(channel->fd());
        return it != Channels_.end() && it->second == channel;
    }
}
