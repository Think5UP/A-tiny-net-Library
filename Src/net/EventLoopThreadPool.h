//
// Created by root on 3/1/23.
//

#ifndef NET_LIB_EVENTLOOPTHREADPOOL_H
#define NET_LIB_EVENTLOOPTHREADPOOL_H

#include <vector>
#include <string>
#include <memory>
#include <functional>

#include "../Base/noncopyable.h"
namespace net_lib{
    class EventLoop;
    class EventLoopThread;

    class EventLoopThreadPool : noncopyable{
    public:
        typedef std::function<void(EventLoop*)> threadInitCallBack;

        EventLoopThreadPool(EventLoop* baseLoop, const std::string &nameArg);
        ~EventLoopThreadPool();

        void start(const threadInitCallBack &cb = threadInitCallBack());
        EventLoop* getNextLoop();
        std::vector<EventLoop*> getAllLoop();

        void setThreadNum(int numThreads) { numThread_ = numThreads; }

        bool started() const { return started_; }
        const std::string name() const { return name_; }

    private:
        EventLoop* baseLoop_;
        int numThread_;
        bool started_;
        size_t next_;
        std::string name_;
        std::vector<std::unique_ptr<EventLoopThread>> threads_;
        std::vector<EventLoop*> loops_;
    };
}

#endif //NET_LIB_EVENTLOOPTHREADPOOL_H
