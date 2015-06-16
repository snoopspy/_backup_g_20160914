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
  ~GAddrInfo();
  bool query(const char* host, const char* port, GErr* err);

  struct addrinfo hints_;
  struct addrinfo* infos_{nullptr};
};
