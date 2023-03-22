//
// Created by root on 2/20/23.
//

#ifndef NET_LIB_TCPSERVER_H
#define NET_LIB_TCPSERVER_H

#include <atomic>
#include <memory>
#include <string>
#include <functional>
#include <unordered_map>

#include "Callbacks.h"
#include "Acceptor.h"
#include "EventLoop.h"
#include "../Base/noncopyable.h"
#include "InetAddress.h"
#include "TCPConnection.h"
#include "EventLoopThreadPool.h"

namespace net_lib{

    class TCPServer : noncopyable{
    public:
        typedef std::function<void(EventLoop *)> ThreadInitCallBack;

        enum Option{
            kNoReusePort,
            kReusePort,
        };

        TCPServer(EventLoop* loop,
                  const InetaAddress& address,
                  const std::string& name,
                  Option option = kNoReusePort);
        ~TCPServer();

        EventLoop *getLoop() const { return loop_; }
        const std::string &name() const { return name_; }
        const std::string &ipPort() const { return ipPort_; }

        void start();

        void setThreadNum(int numThreads);

        void setThreadInitCallBack(const ThreadInitCallBack& cb) { threadInitCallBack_ = cb; }
        void setConnectionCallBack(const ConnectionCallBack& cb) { connectionCallBack_ = cb; }
        void setMessageCallBack(const MessageCallBack& cb) { messageCallBack_ = cb; }
        void setWriteCompleteCallBack(const WriteCompleteCallBack& cb) { writeCompleteCallBack_ = cb; }

    private:
        void newConnection(int sockfd,const InetaAddress& peeraddr);
        void removeConnection(const TCPConnectionPtr& conn);
        void removeConnectionInLoop(const TCPConnectionPtr& conn);

        typedef std::unordered_map<std::string ,TCPConnectionPtr> ConnectionMap;

        EventLoop* loop_;//baseLoop

        std::string ipPort_;//传入的ip和端口号
        std::string name_;

        std::shared_ptr<EventLoopThreadPool> threadPool_;
        std::unique_ptr<Acceptor> acceptor_;

        ConnectionCallBack connectionCallBack_;//处理连接的回调
        MessageCallBack messageCallBack_;//客户端消息的回调
        WriteCompleteCallBack writeCompleteCallBack_;//消息发送完成的回调

        ThreadInitCallBack threadInitCallBack_;//loop线程初始化的回调
        std::atomic_int started_;//TCPServer的状态
        int nextConnId_;//连接索引
        ConnectionMap connections_;//存储所有的TCP连接
    };
}

#endif //NET_LIB_TCPSERVER_H
