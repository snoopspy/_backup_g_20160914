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
#include "g/base/gerr.h"
#include "gsockaddr.h"

// ----------------------------------------------------------------------------
// GSock
// ----------------------------------------------------------------------------
struct GSock {
  GSock() {}
  GSock(const GSock& rhs) : sock_(rhs.sock_) {}
  GSock(int sock) : sock_(sock) {}
  GSock(int domain, int type, int protocol) { socket(domain, type, protocol); }

  operator int() const { return sock_; }

  int accept(GSockAddr *sockAddr, socklen_t *addrLen) {
    int res = ::accept(*this, &sockAddr->addr_, addrLen);
    return res;
  }

  bool bind(GSockAddr* sockAddr, socklen_t addrLen = sizeof(GSockAddr)) {
    int res = ::bind(*this, &sockAddr->addr_, addrLen);
    return  res != -1;
  }

  bool close() {
    return ::close(*this) != -1;
  }

  bool connect(GSockAddr* sockAddr, socklen_t addrLen = sizeof(GSockAddr)) {
    int res = ::connect(*this, &sockAddr->addr_, addrLen);
    if (res == -1) {
      if (GLastErr().code() == EINPROGRESS)
        return true;
      else
        return false;
    }
    return true;
  }

  bool listen(int backLog) {
    int res = ::listen(*this, backLog);
    return res != -1;
  }

  ssize_t recv(void *buf, size_t len, int flags = 0) {
    ssize_t res = ::recv(*this, buf, len, flags);
    return res;
  }

  ssize_t recvfrom(void *buf, size_t len, int flags, GSockAddr* srcAddr, socklen_t *addrLen) {
    ssize_t res = ::recvfrom(*this, buf, len, flags, &srcAddr->addr_, addrLen);
    return res;
  }

  ssize_t recvmsg(struct msghdr *msg, int flags) {
    ssize_t res = ::recvmsg(*this, msg, flags);
    return res;
  }

  ssize_t send(const void *buf, size_t len, int flags = 0) {
    ssize_t res = ::send(*this, buf, len, flags);
    return res;
  }

  ssize_t sendto(const void *buf, size_t len, int flags, GSockAddr *destAddr, socklen_t addrLen) {
    ssize_t res = ::sendto(*this, buf, len, flags, &destAddr->addr_, addrLen);
    return res;
  }

  ssize_t sendmsg(const struct msghdr *msg, int flags) {
    ssize_t res = ::sendmsg(*this, msg, flags);
    return res;
  }

  bool setsockopt(int level, int optname, const void *optval = nullptr, socklen_t optLen = 0) {
    if (optval == nullptr) {
      int temp = 1;
      int res = ::setsockopt(*this, level, optname, &temp, sizeof(temp));
      return res != -1;
    }
    int res = ::setsockopt(*this, level, optname, optval, optLen) != -1;
    return res != -1;
  }

  bool socket(int domain, int type, int protocol) {
    sock_ = ::socket(domain, type, protocol);
    return sock_ != -1;
  }

protected:
  int sock_;
};
