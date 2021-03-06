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
  GAddrInfo() {
    memset(&hints_, 0, sizeof(hints_));
  }

  ~GAddrInfo() {
    if (infos_ != nullptr) {
      freeaddrinfo(infos_);
    }
  }
  GErr* query(QString host, QString port = "");

  struct addrinfo hints_;
  struct addrinfo* infos_{nullptr};
};
