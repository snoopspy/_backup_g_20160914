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

  int accept(GSockAddr *sockAddr, socklen_t *addrLen) { // default arg // gilgil temp 2015.06.09
    DLOG(INFO) << "beg accept sock_=" << sock_;
    int res = ::accept(sock_, &sockAddr->addr_, addrLen);
    DLOG(INFO) << "aft accept sock_=" << sock_ << " res=" << res;
    return res;
  }

  bool bind(struct sockaddr* sockaddr, socklen_t addrLen = sizeof(GSockAddr)) {
    int res = ::bind(sock_, sockaddr, addrLen);
    return res != -1;
  }

  bool bind(GSockAddr* sockAddr, socklen_t addrLen = sizeof(GSockAddr)) {
    int res = ::bind(sock_, &sockAddr->addr_, addrLen);
    return res != -1;
  }

  bool close() {
    DLOG(INFO) << "beg close sock_=" << sock_;
    int sd = sock_;
    int res = ::close(sd);
    if (res == -1) {
      LOG(ERROR) << GLastErr();
    }
    DLOG(INFO) << "aft close sock_=" << sock_ << " res=" << res;
    return res != -1;
  }

  bool connect(GSockAddr* sockAddr, socklen_t addrLen = sizeof(GSockAddr)) {
    int res = ::connect(sock_, &sockAddr->addr_, addrLen);
    if (res == -1) {
      if (GLastErr().code() == EINPROGRESS)
        return true;
      else
        return false;
    }
    return true;
  }

  bool listen(int backLog) {
    int res = ::listen(sock_, backLog);
    return res != -1;
  }

  ssize_t recv(void *buf, size_t len, int flags = 0) {
    ssize_t res = ::recv(sock_, buf, len, flags);
    return res;
  }

  ssize_t recvfrom(void *buf, size_t len, int flags, GSockAddr* srcAddr, socklen_t *addrLen) {
    ssize_t res = ::recvfrom(sock_, buf, len, flags, &srcAddr->addr_, addrLen);
    return res;
  }

  ssize_t recvmsg(struct msghdr *msg, int flags) {
    ssize_t res = ::recvmsg(sock_, msg, flags);
    return res;
  }

  ssize_t send(const void *buf, size_t len, int flags = 0) {
    ssize_t res = ::send(sock_, buf, len, flags);
    return res;
  }

  ssize_t sendto(const void *buf, size_t len, int flags, GSockAddr *destAddr, socklen_t addrLen) {
    ssize_t res = ::sendto(sock_, buf, len, flags, &destAddr->addr_, addrLen);
    return res;
  }

  ssize_t sendmsg(const struct msghdr *msg, int flags) {
    ssize_t res = ::sendmsg(sock_, msg, flags);
    return res;
  }

  bool setsockopt(int level, int optname, const void *optval = nullptr, socklen_t optLen = 0) {
    if (optval == nullptr) {
      int temp = 1;
      int res = ::setsockopt(sock_, level, optname, &temp, sizeof(temp));
      return res != -1;
    }
    int res = ::setsockopt(sock_, level, optname, optval, optLen) != -1;
    return res != -1;
  }

  bool socket(int domain, int type, int protocol) {
    sock_ = ::socket(domain, type, protocol);
    LOG(INFO) << "sock_=" << sock_;
    return sock_ != -1;
  }

  bool shutdown(int how = SHUT_RDWR) {
    int res = ::shutdown(sock_, how);
    return res != -1;
  }

protected:
  int sock_;
};
