#ifndef SOCKET_H_
#define SOCKET_H_

#include "noncopyable.h"

class InetAddress;

class Socket : noncopyable {
 public:
  Socket(int sockfd) : sockfd_(sockfd) {}
  ~Socket();

  int fd() const { return sockfd_; }

  void bindAddress(const InetAddress &localAddress);

  void listen();

  int accept(InetAddress *pearAdress);

  void shutdownWrite();

  void setTcpNoDelay(bool on);
  void setReuseAddr(bool on);
  void setReusePort(bool on);
  void setKeepAlive(bool on);

 private:
  const int sockfd_;
};

#endif  // !SOCKET_H_