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

#include <netdb.h>
#include "g/base/gerr.h"

// ----------------------------------------------------------------------------
// GAddrInfo
// ----------------------------------------------------------------------------
struct GAddrInfo {
  GAddrInfo() : info_(nullptr) {}

  ~GAddrInfo() {
    if (info_ != nullptr) {
      freeaddrinfo(info_);
      info_ = nullptr;
    }
  }

  bool query(const char* host, GErr** err = nullptr);
  bool query(const char* host, const char* port, GErr** err = nullptr);
  bool query(const struct addrinfo& hints, const char* host, GErr** err = nullptr);
  bool query(const struct addrinfo& hints, const char* host, const char* port, GErr** err = nullptr);

  struct addrinfo* info_{nullptr};
};
