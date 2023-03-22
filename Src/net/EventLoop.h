//
// Created by root on 2/20/23.
//

#ifndef NET_LIB_EVENTLOOP_H
#define NET_LIB_EVENTLOOP_H

#include <mutex>
#include <atomic>
#include <vector>
#include <memory>
#include <functional>

#include "../Base/noncopyable.h"
#include "../Base/Timestamp.h"
#include "CurrentThread.h"

namespace net_lib{
    class Channel;
    class Poller;

    class EventLoop : noncopyable{
        typedef std::vector<Channel*> ChannelList;
    public:
        typedef std::function<void()> Functor;

        EventLoop();
        ~EventLoop();

        //事件循环的启动函数
        void loop();
        //退出函数
        void quit();

        //获取poll返回的时间
        Timestamp pollReturnTime() const {return pollReturnTime_;}

        //在当前loop中执行回调
        void runInLoop(Functor cb);
        //将回调cb放入队列中，唤起loop的线程，然后执行回调
        void queueInLoop(Functor cb);

        void wakeup();

        void updateChannel(Channel *);
        void removeChannel(Channel *);
        bool hasChannel(Channel *);

        bool isInLoopThread(){return threadId_ == CurrentThread::tid();}
    private:
        void handleRead();//wake up
        void doPendingFunctors();//执行回调函数

        std::atomic_bool looping_;
        std::atomic_bool quit_;//表示是否退出
        std::atomic_bool callingPendingFunctors_;//当前loop是否需要执行回调的标志

        const pid_t threadId_;//当前loop所在的线程 用于比较loop是否在自己的线程中
        Timestamp pollReturnTime_;
        std::unique_ptr<Poller> poller_;

        int wakeupFd_;//mainLoop向subloop::wakeupFd写数据唤醒  如果需要唤醒某个EventLoop执行异步操作，就向其wakeupFd_写入数据。
        std::unique_ptr <Channel> wakeupChannel_;

        ChannelList activeChannels_; //存放活跃的Channel
        Channel* currentActiveChannel_;//当前正在处理的活跃的Channel

        std::mutex mutex_;//为了保护pendingFunctors_的线程安全
        std::vector<Functor> pendingFunctors_;//存放loop跨线程需要执行的所有的回调操作   如果涉及跨线程调用函数时，会将函数储存到pendingFunctors_这个任务队列中。
    };
}
#endif //NET_LIB_EVENTLOOP_H
