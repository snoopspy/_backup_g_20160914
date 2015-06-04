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

#include <unistd.h> // for close
#include "gsockaddr.h"

// ----------------------------------------------------------------------------
// GSock
// ----------------------------------------------------------------------------
struct GSock {
  GSock() {}
  GSock(const GSock& rhs) { sock_ = rhs.sock_; }
  GSock(int sock) : sock_(sock) {}
  GSock(int domain, int type, int protocol) { socket(domain, type, protocol); }

  operator int() const { return sock_; }

  int accept(GSockAddr *sockAddr, socklen_t *addrLen) {
    return ::accept((int)*this, &sockAddr->addr_, addrLen);
  }

  bool bind(GSockAddr* sockAddr, socklen_t addrLen = sizeof(GSockAddr)) {
    return ::bind((int)*this, &sockAddr->addr_, addrLen) != -1;
  }

  bool close() {
    return ::close((int)*this) != -1;
  }

  bool connect(GSockAddr* sockAddr, socklen_t addrLen = sizeof(GSockAddr)) {
    return ::connect((int)*this, &sockAddr->addr_, addrLen) != -1;
  }

  bool listen(int backLog) {
    return ::listen((int)*this, backLog) != -1;
  }

  ssize_t recv(void *buf, size_t len, int flags = 0) {
    return ::recv((int)*this, buf, len, flags);
  }

  ssize_t recvfrom(void *buf, size_t len, int flags, GSockAddr* srcAddr, socklen_t *addrLen) {
    return ::recvfrom((int)*this, buf, len, flags, &srcAddr->addr_, addrLen);
  }

  ssize_t recvmsg(struct msghdr *msg, int flags) {
    return ::recvmsg((int)*this, msg, flags);
  }

  ssize_t send(const void *buf, size_t len, int flags = 0) {
    return ::send((int)*this, buf, len, flags);
  }

  ssize_t sendto(const void *buf, size_t len, int flags, GSockAddr *destAddr, socklen_t addrLen) {
    return ::sendto((int)*this, buf, len, flags, &destAddr->addr_, addrLen);
  }

  ssize_t sendmsg(const struct msghdr *msg, int flags) {
    return ::sendmsg((int)*this, msg, flags);
  }

  bool setsockopt(int level, int optName, const void *optVal = nullptr, socklen_t optLen = 0) {
    if (optVal == nullptr) {
      int temp = 1;
      return ::setsockopt((int)*this, level, optName, &temp, sizeof(temp)) != -1;
    }
    return ::setsockopt((int)*this, level, optName, optVal, optLen) != -1;
  }

  bool socket(int domain, int type, int protocol) {
    sock_ = ::socket(domain, type, protocol);
    return sock_ != -1;
  }

protected:
  int sock_;
};
