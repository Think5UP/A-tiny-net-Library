//
// Created by root on 2/20/23.
//
#ifndef NET_LIB_CHANNEL_H
#define NET_LIB_CHANNEL_H

#include <memory>
#include <functional>

#include "../Base/Timestamp.h"
#include "../Base/noncopyable.h"

namespace net_lib{
    class EventLoop;

    //封装sockfd以及感兴趣的event，绑定了返回的具体发生的事件
    class Channel : public noncopyable{
    public:
        typedef std::function<void()> EventCallBack;
        typedef std::function<void(Timestamp)> ReadEventCallBack;

        Channel(EventLoop* loop,int fd);
        ~Channel();
        //事件处理
        void handleEvent(Timestamp receiveTime);
        //设置回调事件对象,cb是函数对象，这里使用std::move将cb转为右值，避免拷贝
        void setReadEventCallBack(ReadEventCallBack cb){ readEventCallBack_ = std::move(cb); }
        void setWriteEventCallBack(EventCallBack cb){ writeEventCallBack_ = std::move(cb); }
        void setCloseEventCallBack(EventCallBack cb){ closeEventCallBack_ = std::move(cb); }
        void setErrorEventCallBack(EventCallBack cb){ errorEventCallBack_ = std::move(cb); }

        //将这个channel绑定到智能指针管理的所有者对象,防止在handleEvent中销毁所有者对象
        void tie(const std::shared_ptr<void>&);

        int fd() const {return fd_;}
        int events() const {return events_;}
        void setREvent(int ev) {rEvents_ = ev;}

        //将感兴趣的事件注册到Poller中
        void enableReadEvent() {events_ |= kReadEvent;update();}
        void disableReadEvent() {events_ &= ~kReadEvent;update();}
        void enableWriteEvent() {events_ |= kWriteEvent;update();}
        void disableWriteEvent() {events_ &= ~kWriteEvent;update();}
        void disAllEvent() {events_ = kNoneEvent;update();}
        bool isReading() const {return events_ & kReadEvent;}
        bool isWriting() const {return events_ & kWriteEvent;}
        bool isNoneEvent() const {return events_ & kNoneEvent;}

        int index() const {return index_;}
        void setIndex(int idx) {index_ = idx;}

        EventLoop* ownerLoop() const {return loop_;}
        void remove();
    private:

        void update();
        void handleEventWithGuard(Timestamp receiveTime);

        static const int kNoneEvent;//不对任何事件感兴趣
        static const int kReadEvent;//对读事件感兴趣
        static const int kWriteEvent;//对写事件感兴趣

        EventLoop* loop_;//事件循环
        const int fd_; //监听的文件描述符

        int events_;//感兴趣的事件
        int rEvents_;//返回的发生的事件
        int index_;

        std::weak_ptr<void> tie_;//监听自己的智能指针防止move之后再次使用自己
        bool tied_;

        //从rEvent知道最终发生的事件，并且由这个事件来执行相应的回调函数.
        ReadEventCallBack readEventCallBack_;
        EventCallBack writeEventCallBack_;
        EventCallBack closeEventCallBack_;
        EventCallBack errorEventCallBack_;
    };
}

#endif //NET_LIB_CHANNEL_H
