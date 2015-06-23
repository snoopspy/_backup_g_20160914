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

  GErr* query(const char* host);
  GErr* query(const char* host, const char* port);
  GErr* query(const struct addrinfo& hints, const char* host);
  GErr* query(const struct addrinfo& hints, const char* host, const char* port);

  struct addrinfo* info_{nullptr};
};
