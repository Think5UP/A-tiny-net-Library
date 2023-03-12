//
// Created by root on 2/21/23.
//

#ifndef NET_LIB_EPOLLPOLLER_H
#define NET_LIB_EPOLLPOLLER_H

#include <vector>
#include <unistd.h>
#include <sys/epoll.h>

#include "Poller.h"

namespace net_lib{
    class EventLoop;
    class Channel;

    class EpollPoller : public Poller{
        typedef std::vector<epoll_event> EventList;
    public:
        EpollPoller(EventLoop* loop);
        ~EpollPoller() override;

        Timestamp poll(int timeoutMS,ChannelList* activeChannels) override;
        void updateChannel(Channel* channel) override;
        void removeChannel(Channel* channel) override;
    private:

        //默认监听事件数量
        static const int kInitEventListSize = 16;
        //填充活跃的连接
        void fillActiveChannel(int numEvents,ChannelList* activeChannels) const;
        //更新channel
        void update(int operation,Channel* channel);

        int epollfd_;
        EventList events_;
    };
}

#endif //NET_LIB_EPOLLPOLLER_H
