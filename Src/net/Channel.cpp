//
// Created by root on 2/20/23.
//
#include <sys/epoll.h>

#include "../Base/Logger.h"
#include "Channel.h"
#include "EventLoop.h"

namespace net_lib{
    const int Channel::kNoneEvent = 0;//不对任何事件感兴趣
    const int Channel::kReadEvent = EPOLLIN | EPOLLPRI;//对读事件感兴趣
    const int Channel::kWriteEvent = EPOLLOUT;//对写事件感兴趣

    Channel::Channel(EventLoop *loop, int fd)
            : loop_(loop),
              fd_(fd),
              events_(0),
              rEvents_(0),
              index_(-1),
              tied_(false){}

    Channel::~Channel() {}

    void Channel::tie(const std::shared_ptr<void> &obj) {
        //weak_ptr指向 obj
        tie_ = obj;
        tied_ = true;
    }

    //事件改变后，更新该fd相应事件
    void Channel::update() {
        //通过EventLoop更新poller里的channel
        loop_->updateChannel(this);
    }

    //从poller中删除掉当前的fd
    void Channel::remove() {
        loop_->removeChannel(this);
    }

    void Channel::handleEvent(Timestamp receiveTime) {
        /**
        * 调用了Channel::tie得会设置tid_=true
        * 而TcpConnection::connectEstablished会调用channel_->tie(shared_from_this());
        * 所以对于TcpConnection::channel_ 需要多一份强引用的保证以免用户误删TcpConnection对象
        */
        if(tied_)
        {
            //提升tie_，增加对象的引用计数，防止TCPConnection被意外删除
            std::shared_ptr<void> guard = tie_.lock();
            if(guard){
                handleEventWithGuard(receiveTime);
            }
        } else{
            handleEventWithGuard(receiveTime);
        }
    }

    //根据相应事件执行Channel保存的回调函数
    void Channel::handleEventWithGuard(Timestamp receiveTime) {
        LOG_INFO("Channel handleEvent rEvent = %d\n",rEvents_);
        //对端关闭连接
        if((rEvents_ & EPOLLHUP) && !(rEvents_ & EPOLLIN)){
            if(closeEventCallBack_){
                closeEventCallBack_();
            }
        }
        if(rEvents_ & EPOLLERR){
            if (errorEventCallBack_) {
                errorEventCallBack_();
            }
        }
        if(rEvents_ & (EPOLLIN | EPOLLPRI)) {
            if(readEventCallBack_) {
                readEventCallBack_(receiveTime);
            }
        }
        if(rEvents_ & EPOLLOUT) {
            if (writeEventCallBack_) {
                writeEventCallBack_();
            }
        }
    }
}
