//
// Created by root on 2/28/23.
//

#include "EventLoop.h"
#include "EventLoopThread.h"

namespace net_lib{
    EventLoopThread::EventLoopThread(const threadInitCallBack &cb,
                                     const std::string &name) : exiting_(false),
                                                                thread_(std::bind(&EventLoopThread::threadFunc, this),name),
                                                                loop_(nullptr),
                                                                mutex_(),
                                                                callBack_(cb),
                                                                cond_(){}

    EventLoopThread::~EventLoopThread() {
        exiting_ = true;
        loop_->quit();
        thread_.join();
    }

    EventLoop *EventLoopThread::startLoop() {
        thread_.start();

        EventLoop* loop = nullptr;
        {
            //上锁等待loop创建
            std::unique_lock<std::mutex> lock(mutex_);
            while(loop == nullptr){
                cond_.wait(lock);
            }
            loop = loop_;
        }
        return loop;
    }

    void EventLoopThread::threadFunc() {
        EventLoop loop;
        if(callBack_){
            callBack_(&loop);
        }
        {
            std::unique_lock<std::mutex> lock(mutex_);
            loop_ = &loop;
            cond_.notify_one();
        }
        loop.loop();
        std::unique_lock<std::mutex> lock(mutex_);
        loop_ = nullptr;
    }
}
