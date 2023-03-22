//
// Created by root on 2/27/23.
//

#ifndef NET_LIB_THREAD_H
#define NET_LIB_THREAD_H

#include <atomic>
#include <thread>
#include <memory>
#include <unistd.h>
#include <functional>

#include "noncopyable.h"

namespace net_lib{
    class Thread : noncopyable{
    public:
        typedef std::function<void()> threadFunc;

        explicit Thread(threadFunc func,const std::string& name = std::string());
        ~Thread();

        void start();
        void join();

        bool started() const {return started_;}
        bool joined() const {return joined_;}
        pid_t tid() const {return tid_;}
        const std::string& name() const {return name_;}
        static int numCreated() {return numCreated_;}
    private:
        void setDefaultName();
        bool started_;
        bool joined_;
        std::shared_ptr<std::thread> thread_;
        pid_t tid_;
        threadFunc func_;
        std::string name_;
        static std::atomic_int32_t numCreated_;
    };
}

#endif //NET_LIB_THREAD_H
