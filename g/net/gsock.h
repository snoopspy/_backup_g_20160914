// ----------------------------------------------------------------------------
//
// G Library
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#pragma once

#include "g/base/gerr.h"
#include "gsockaddr.h"

// ----------------------------------------------------------------------------
// Defines
// ----------------------------------------------------------------------------
#define INVALID_SOCKET -1

// ----------------------------------------------------------------------------
// GSock
// ----------------------------------------------------------------------------
struct GSock final {
  GSock() {}
  GSock(const GSock& rhs) : sock_(rhs.sock_) {}
  GSock(int sock) : sock_(sock) {}
  GSock(int domain, int type, int protocol) { socket(domain, type, protocol); }

  operator int() const { return sock_; }

  int accept(GSockAddr *sockAddr = nullptr, socklen_t *addrLen = nullptr);
  bool bind(struct sockaddr* sockAddr, socklen_t addrLen = sizeof(GSockAddr));
  bool bind(GSockAddr* sockAddr, socklen_t addrLen = sizeof(GSockAddr));
  bool close();
  bool connect(struct sockaddr* sockAddr, socklen_t addrLen = sizeof(GSockAddr));
  bool connect(GSockAddr* sockAddr, socklen_t addrLen = sizeof(GSockAddr));
  bool listen(int backLog);
  ssize_t recv(void *buf, size_t len, int flags = 0);
  ssize_t recvfrom(void *buf, size_t len, int flags, GSockAddr* srcAddr, socklen_t *addrLen);
  ssize_t recvmsg(struct msghdr *msg, int flags);
  ssize_t send(const void *buf, size_t len, int flags = 0);
  ssize_t sendto(const void *buf, size_t len, int flags, GSockAddr *destAddr, socklen_t addrLen);
  ssize_t sendmsg(const struct msghdr *msg, int flags);
  bool setsockopt(int level, int optName, const void *optVal = nullptr, socklen_t optLen = 0);
  bool socket(int domain, int type, int protocol);
  bool shutdown(int how = SHUT_RDWR);
  bool setNonblock();

protected:
  int sock_;
};
