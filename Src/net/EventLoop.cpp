//
// Created by root on 2/20/23.
//

#include <memory>
#include <fcntl.h>
#include <unistd.h>
#include <sys/eventfd.h>

#include "../Base/Logger.h"
#include "Poller/Poller.h"
#include "Channel.h"
#include "EventLoop.h"



namespace net_lib{
    //保证当前线程只能创建一个loop
    __thread EventLoop* t_loopInThisThread = nullptr;// threadLocal
    const int kPollTimeMS = 10000;

    //创建并返回一个非阻塞的负责线程间等待/通信的文件描述符
    int createEventFd(){
        int evfd = ::eventfd(0,EFD_NONBLOCK | EFD_CLOEXEC);
        if(evfd < 0){
            LOG_FATAL("eventfd error : %d\n",errno);
        }
        return evfd;
    }

    EventLoop::EventLoop() : looping_(false),
                             quit_(false),
                             callingPendingFunctors_(false),
                             threadId_(CurrentThread::tid()),
                             poller_(Poller::newDefaultPoller(this)),
                             wakeupFd_(createEventFd()),
                             wakeupChannel_(new Channel(this,wakeupFd_)),
                             currentActiveChannel_(nullptr){
        LOG_DEBUG("EventLoop create %p , thread is %d\n", this,threadId_);
        if(t_loopInThisThread){
            LOG_FATAL("this thread is create an EventLoop");
        } else {
            //用当前线程的静态变量存储线程号
            t_loopInThisThread = this;
        }
        //设置读事件的回调函数
        wakeupChannel_->setReadEventCallBack(std::bind(&EventLoop::handleRead, this));
        //设置wakeupChannel_关系读事件并且将wakeupChannel_注册到Poller中。
        wakeupChannel_->enableReadEvent();
    }

    EventLoop::~EventLoop() {
        wakeupChannel_->disAllEvent();
        wakeupChannel_->remove();
        ::close(wakeupFd_);
        t_loopInThisThread = nullptr;
    }

    void EventLoop::loop() {
        looping_ = true;
        quit_ = false;
        LOG_INFO("%p is starting loop \n", this);
        while(!quit_){
            activeChannels_.clear();
            pollReturnTime_ = poller_->poll(kPollTimeMS,&activeChannels_);
            for(Channel* channel : activeChannels_){
                channel->handleEvent(pollReturnTime_);
            }
            doPendingFunctors();
        }
        looping_ = false;
        LOG_INFO("%p is stopping loop \n",this);
    }

    void EventLoop::quit() {
        quit_ = true;
        if(isInLoopThread()){
            wakeup();
        }
    }

    void EventLoop::runInLoop(Functor cb) {
        if(isInLoopThread()){
            cb();
        } else {
            queueInLoop(cb);
        }
    }

    void EventLoop::queueInLoop(Functor cb) {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            pendingFunctors_.emplace_back(cb);
        }
        //唤醒需要执行回调的loop相应的线程
        //加入callingPendingFunctors_是为了后续如果添加了新的回调也能把新添加的回调唤醒执行处理，防止loop阻塞
        if(!isInLoopThread() || callingPendingFunctors_){
            wakeup();
        }
    }

    void EventLoop::wakeup() {
        uint64_t one;
        ssize_t n = write(wakeupFd_,&one,sizeof(one));
        if(n != sizeof(one)){
            LOG_ERROR("EventLoop::wakeup write %lu bytes instead of 8",n);
        }
    }

    void EventLoop::removeChannel(Channel *channel) {
        poller_->removeChannel(channel);
    }
    void EventLoop::updateChannel(Channel *channel) {
        poller_->updateChannel(channel);
    }
    bool EventLoop::hasChannel(Channel *channel) {
        return poller_->hasChannel(channel);
    }

//private:
    void EventLoop::handleRead() {
        uint64_t one = 1;
        ssize_t n = read(wakeupFd_,&one,sizeof(one));
        if(n != sizeof(one)){
            LOG_ERROR("EventLoop::handelRead read %lu bytes instead of 8",n);
        }
    }

    void EventLoop::doPendingFunctors() {

    }

}


