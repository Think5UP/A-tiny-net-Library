//
// Created by root on 2/28/23.
//

#ifndef NET_LIB_EVENTLOOPTHREAD_H
#define NET_LIB_EVENTLOOPTHREAD_H

#include <mutex>
#include <functional>
#include <condition_variable>

#include "../Base/Thread.h"
#include "../Base/noncopyable.h"

namespace net_lib{
    class EventLoop;
    class EventLoopThread : noncopyable{
    public:
        typedef std::function<void(EventLoop *)> threadInitCallBack;

        EventLoopThread(const threadInitCallBack &cb = threadInitCallBack(),const std::string &name = std::string());
        ~EventLoopThread();

        EventLoop* startLoop();
    private:
        void threadFunc();
        bool exiting_;
        Thread thread_;
        EventLoop* loop_;
        std::mutex mutex_;
        threadInitCallBack callBack_;
        std::condition_variable cond_;
    };
}

#endif //NET_LIB_EVENTLOOPTHREAD_H
