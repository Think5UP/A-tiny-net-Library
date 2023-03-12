//
// Created by root on 3/6/23.
//

#ifndef NET_LIB_TCPCONNECTION_H
#define NET_LIB_TCPCONNECTION_H

#include <atomic>
#include <memory>
#include <string>

#include "Buffer.h"
#include "Callbacks.h"
#include "InetAddress.h"
#include "../Base/Timestamp.h"

namespace net_lib{

    class Socket;
    class Channel;
    class EventLoop;

class TCPConnection : noncopyable,public std::enable_shared_from_this<TCPConnection>{
    public:
        TCPConnection(EventLoop* loop,
                      const std::string& name,
                      int sockfd,
                      const InetaAddress& localAddr,
                      const InetaAddress& peerAddr);
        ~TCPConnection();

        EventLoop* getLoop() const { return loop_; }
        const std::string& getName() const { return name_; }
        const InetaAddress& localAddr() const { return localAddr_; }
        const InetaAddress& peerAddr() const { return peerAddr_; }

        bool connected() const { return state_ == kConnected; }

        const std::string StateToString();

        // 发送数据
        void send(const std::string &buf);
        void send(Buffer *buf);

        // 关闭连接
        void shutdown();

        void setConnectionCallBack(const ConnectionCallBack& cb){
            connectionCallBack_ = cb;
        }
        void setCloseCallBack(const CloseCallBack& cb){
            closeCallBack_ = cb;
        }
        void setWriteCompleteCallBack(const WriteCompleteCallBack& cb){
            writeCompleteCallBack_ = cb;
        }
        void setHighWaterMarkCallBack(const HighWaterMarkCallBack& cb,size_t HighWaterMark){
            highWaterMark_ = HighWaterMark;
            highWaterMarkCallBack_ = cb;
        }
        void setMessageCallBack(const MessageCallBack& cb){
            messageCallBack_ = cb;
        }

        void ConnectEstablish();
        void ConnectDestroy();

    private:
    enum StateE{
        kDisConnected = 0,
        kConnecting = 1,
        kConnected = 2,
        kDisConnecting = 3,
        //ERROR = 4,
    };

    void handleRead(Timestamp receiveTime);
    void handelWrite();
    void handleClose();
    void handleError();

    void setState(StateE state) { state_ =  state; }

    void sendInLoop(const std::string& message);
    void sendInLoop(const void* message, size_t len);

    void shutdownInLoop();

    EventLoop* loop_;
    const std::string name_;
//    std::atomic_int state_;
    StateE state_;
    bool reading_;


    const InetaAddress localAddr_;
    const InetaAddress peerAddr_;

    std::unique_ptr<Socket> socket_;
    std::unique_ptr<Channel> channel_;

    ConnectionCallBack connectionCallBack_;
    CloseCallBack closeCallBack_;
    WriteCompleteCallBack writeCompleteCallBack_;
    HighWaterMarkCallBack highWaterMarkCallBack_;
    MessageCallBack messageCallBack_;
    size_t highWaterMark_;

    Buffer inputBuffer_;
    Buffer outputBuffer_;
    };
}

#endif //NET_LIB_TCPCONNECTION_H
