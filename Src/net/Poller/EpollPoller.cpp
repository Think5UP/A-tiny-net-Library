//
// Created by root on 2/21/23.
//

#include <cerrno>
#include <cassert>

#include "../Channel.h"
#include "EpollPoller.h"
#include "../../Base/Logger.h"

namespace net_lib{

    const int kNew = -1;//某个Channel还未添加至Poller  //Channel中的index_初始化为-1就是为了表示Channel的状态
    const int kAdded = 1;//某个Channel已经添加到Poller
    const int kDeleted = 2;//某个Channel已经被Poller删除

    EpollPoller::EpollPoller(EventLoop *loop)
            : Poller(loop),
              epollfd_(::epoll_create1(EPOLL_CLOEXEC)),
              events_(kInitEventListSize){
            if(epollfd_ < 0){
                LOG_FATAL("Epoll_create() error:%d\n",errno);
            }
    }

    EpollPoller::~EpollPoller() {
        ::close(epollfd_);
    }

    //通过epoll_wait获取活跃的channel,然后填充EventLoop的ChannelList,这样能保证一定是活跃的channel被回调函数处理
    Timestamp EpollPoller::poll(int timeoutMS, ChannelList *activeChannels) {
        size_t numEvent = ::epoll_wait(epollfd_,&(*events_.begin()),static_cast<int>(events_.size()),timeoutMS);
        Timestamp now(Timestamp::now());
        //防止切换线程时errno改变，所以需要将errno存储
        int saveError = errno;
        //监听到事件发生
        if(numEvent > 0){
            fillActiveChannel(numEvent,activeChannels);
            //events_的自动扩容
            if(numEvent == events_.size()){
                events_.resize(events_.size() * 2);
            }
        } else if(numEvent == 0){ //超时未有使事件发生
            LOG_DEBUG("%s nothing happened",__FUNCTION__);
        } else {//出错
            //排除是因为系统中断产生的错误
            if(saveError != EINTR){
                errno = saveError;
                LOG_ERROR("EpollPoller::Poller error!");
            }
        }
        return now;
    }

    void EpollPoller::updateChannel(Channel *channel) {
        //获取Channel的状态
        const int index = channel->index();
        LOG_INFO("fd= %d , events= %d , index= %d",channel->fd(),channel->events(),index);
        if(index == kNew || index == kDeleted){
            int fd = channel->fd();
            if(index == kNew){
                Channels_[fd] = channel;
            } else { //index == kDeleted
                assert(Channels_.find(fd) != Channels_.end());
                assert(Channels_[fd] == channel);
            }
            channel->setIndex(kAdded);
            update(EPOLL_CTL_ADD,channel);
        } else { //index == kAdded
            if(channel->isNoneEvent()){
                update(EPOLL_CTL_DEL, channel);
                channel->setIndex(kDeleted);
            } else {
                update(EPOLL_CTL_MOD,channel);
            }
        }
    }

    void EpollPoller::removeChannel(Channel *channel) {
        int fd = channel->fd();
        Channels_.erase(fd);
        int index = channel->index();
        /*确认channel已经在ChannelMap中注册过能够找到
         *同时index为kAdded|kDeleted，并且channel已经没有关注的事件
         *那就将channel从ChannelMap中删除
         *如果index==kAdded那就还需要将channel从epoll中删除
         */
        assert(Channels_.find(fd) != Channels_.end());
        assert(Channels_[fd] == channel);
        assert(channel->isNoneEvent());
        assert(index == kAdded || index == kDeleted);

        Channels_.erase(fd);
        if(index == kAdded){
            update(EPOLL_CTL_DEL,channel);
        }
        channel->setIndex(kNew);
    }

    void EpollPoller::fillActiveChannel(int numEvent, ChannelList *activeChannels) const {
        for (int i = 0; i < numEvent; ++i) {
            Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
            channel->setREvent(events_[i].events);
            activeChannels->push_back(channel);
        }
    }

    void EpollPoller::update(int operation, Channel *channel) {
        int fd = channel->fd();
        struct epoll_event event;
        memset(&event,0, sizeof(event));
        event.events = channel->events();
        event.data.fd = fd;
        event.data.ptr = channel;
        if(::epoll_ctl(epollfd_,operation,fd,&event) < 0){
            if (operation == EPOLL_CTL_DEL) {
                LOG_ERROR("EPOLL_CTL_DEL error:%d\n",errno);
            } else {
                LOG_FATAL("EPOLL_CTL_ADD error:%d\n",errno);
            }
        }
    }
}