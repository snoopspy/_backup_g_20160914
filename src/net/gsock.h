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
  GSock(int domain, int type, int protocol);
  GSock(const GSock& rhs) { sock_ = rhs.sock_; }

  operator int() const { return sock_; }

  bool bind(GSockAddr& sockAddr, socklen_t addrlen);
  bool setsockopt(int level, int optname, const void *optval, socklen_t optlen);
  bool socket(int domain, int type, int protocol);

protected:
  int sock_;
};
