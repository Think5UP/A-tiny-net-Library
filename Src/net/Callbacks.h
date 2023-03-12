//
// Created by root on 3/6/23.
//

#ifndef NET_LIB_CALLBACKS_H
#define NET_LIB_CALLBACKS_H

#include <memory>
#include <functional>

namespace net_lib{
    class Buffer;
    class Timestamp;
    class TCPConnection;

    typedef std::shared_ptr<TCPConnection> TCPConnectionPtr;
    typedef std::function<void(const TCPConnectionPtr&)> ConnectionCallBack;
    typedef std::function<void(const TCPConnectionPtr&)> CloseCallBack;
    typedef std::function<void(const TCPConnectionPtr&)> WriteCompleteCallBack;
    typedef std::function<void(const TCPConnectionPtr&, size_t)> HighWaterMarkCallBack;

    typedef std::function<void(const TCPConnectionPtr&,
                               Buffer*,
                               Timestamp)> MessageCallBack;


}

#endif //NET_LIB_CALLBACKS_H
