#ifndef ACCEPTOR_H_
#define ACCEPTOR_H_

#include "Channel.h"
#include "noncopyable.h"
#include "Socket.h"

class EventLoop;
class InetAddress;

class Acceptor : noncopyable {
 public:
  using NewConnectionCallback =
      std::function<void(int sockfd, const InetAddress &)>;

  Acceptor(EventLoop *loop, const InetAddress &listenAddr, bool reusePort);
  ~Acceptor();

  void setNewConnectionCallback(const NewConnectionCallback &cb) {
    newConnectionCallback_ = cb;
  }

  bool listenning() const { return listenning_; }
  void listen();

 private:
  void handleRead();

  NewConnectionCallback newConnectionCallback_;

  EventLoop *loop_;
  Socket acceptSocket_;
  Channel acceptChannel_;

  bool listenning_;
};

#endif  // !ACCEPTOR_H_