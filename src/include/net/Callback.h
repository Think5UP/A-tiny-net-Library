#ifndef CALLBACK_H_
#define CALLBACK_H_

#include <functional>
#include <memory>

class Buffer;
class TcpConnection;
class Timestamp;

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using ConnectionCallback = std::function<void(const TcpConnectionPtr &)>;
using CloseCallback = std::function<void(const TcpConnectionPtr &)>;
using WriteCompleteCallback = std::function<void(const TcpConnectionPtr &)>;
using HighWaterMarkCallback =
    std::function<void(const TcpConnectionPtr &, size_t)>;

using MessageCallback =
    std::function<void(const TcpConnectionPtr &, Buffer *, Timestamp)>;

#endif  // !CALLBACK_H_