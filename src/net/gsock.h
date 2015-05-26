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

#include <sys/socket.h>

// ----------------------------------------------------------------------------
// GSock
// ----------------------------------------------------------------------------
struct GSock {
  GSock(int domain = AF_INET, int type = SOCK_STREAM, int protocol = 0);
  GSock(const GSock& rhs) { sock_ = rhs.sock_; }

  operator int() const { return sock_; }

protected:
  int sock_;
};
