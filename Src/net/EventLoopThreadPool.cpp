//
// Created by root on 3/1/23.
//

#include "EventLoop.h"
#include "EventLoopThread.h"
#include "EventLoopThreadPool.h"

namespace net_lib{
    EventLoopThreadPool::EventLoopThreadPool(EventLoop *baseLoop,
                                             const std::string &nameArg) : baseLoop_(baseLoop),
                                                                           numThread_(0),
                                                                           started_(false),
                                                                           next_(0),
                                                                           name_(nameArg){}
    EventLoopThreadPool::~EventLoopThreadPool() {
        //do nothing it's stack variable
    }

    void EventLoopThreadPool::start(const threadInitCallBack &cb) {
        started_ = true;
        for(int i = 0; i < numThread_; ++i){
            char buf[name_.size() + 32];
            snprintf(buf, sizeof(buf),"%s%d",name_.c_str(),i);
            EventLoopThread *t = new EventLoopThread(cb,buf);
            threads_.push_back(std::unique_ptr<EventLoopThread>(t));
            loops_.push_back(t->startLoop());
        }
        if(numThread_ == 0 && cb){
            cb(baseLoop_);
        }
    }

    //mainloop轮询将channel分配给subloop
    //返回loops_中的下一个loop
    EventLoop *EventLoopThreadPool::getNextLoop() {
        EventLoop *loop = baseLoop_;
        if(!loops_.empty()){
            loop = loops_[next_];
            ++next_;
            if(next_ >= loops_.size()){
                next_ = 0;
            }
        }
        return loop;
    }

    std::vector<EventLoop *> EventLoopThreadPool::getAllLoop() {
        if(loops_.empty()){
            return std::vector<EventLoop*>(1,baseLoop_);
        } else {
            return loops_;
        }
    }
}