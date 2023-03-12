//
// Created by root on 2/21/23.
//

#ifndef NET_LIB_POLLER_H
#define NET_LIB_POLLER_H

#include <map>
#include <vector>

#include "../../Base/Timestamp.h"
#include "../../Base/nocopyable.h"

namespace net_lib{

    class EventLoop;
    class Channel;

    class Poller : public noncopyable{
    public:
        typedef std::vector<Channel*> ChannelList;

        Poller(EventLoop* loop);

        virtual ~Poller();

        //监听事件和fd，返回调用epoll_wait时间
        virtual Timestamp poll(int timeoutMS,ChannelList* activeChannel) = 0;

        //更新事件
        //是层层递进的 Channel::update()->EventLoop::updateChannel->Poller::updateChannel
        virtual void updateChannel(Channel* channel) = 0;


        virtual void removeChannel(Channel *channel) = 0;

        virtual bool hasChannel(Channel* channel) const;

        static Poller* newDefaultPoller(EventLoop* loop);
    //需要EPollPoller继承所以设置为protected
    protected:
        typedef std::map<int,Channel*> ChannelMap;
        ChannelMap Channels_;
    private:
        EventLoop* ownerLoop_;
    };
}

#endif //NET_LIB_POLLER_H
