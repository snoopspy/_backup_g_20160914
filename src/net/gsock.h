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

#include "gsockaddr.h"

// ----------------------------------------------------------------------------
// GSock
// ----------------------------------------------------------------------------
struct GSock {
  GSock() {}
  GSock(int sock) : sock_(sock) {}
  GSock(int domain, int type, int protocol);
  GSock(const GSock& rhs) { sock_ = rhs.sock_; }

  operator int() const { return sock_; }

  int accept(GSockAddr *sockAddr, socklen_t *addrLen);
  bool bind(GSockAddr* sockAddr, socklen_t addrLen = sizeof(GSockAddr));
  bool close();
  bool connect(GSockAddr* sockAddr, socklen_t addrLen);
  bool listen(int backLog);
  ssize_t recv(void *buf, size_t len, int flags);
  ssize_t recvfrom(void *buf, size_t len, int flags, GSockAddr* srcAddr, socklen_t *addrLen);
  ssize_t recvmsg(struct msghdr *msg, int flags);
  ssize_t send(const void *buf, size_t len, int flags);
  ssize_t sendto(const void *buf, size_t len, int flags, GSockAddr *destAddr, socklen_t addrLen);
  ssize_t sendmsg(const struct msghdr *msg, int flags);
  bool setsockopt(int level, int optName, const void *optVal, socklen_t optLen);
  bool socket(int domain, int type, int protocol);

protected:
  int sock_;
};
