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

#include <netinet/in.h>
#include "g/base/gerr.h"
#include "gip.h"
#include "gip6.h"

// ----------------------------------------------------------------------------
// GSockAddr
// ----------------------------------------------------------------------------
union GSockAddr {
  GSockAddr();
  GSockAddr(struct sockaddr* addr);
  GSockAddr(struct sockaddr_in* addrIn);
  GSockAddr(struct sockaddr_in6* addrIn6);

  GErr* init(const char* host, const char* port);

  int family();
  GIp ip();
  GIp6 ip6();
  quint16 port();

  struct sockaddr addr_; // 16 bytes
  struct sockaddr_in addrIn_; // 16 bytes
  struct sockaddr_in6 addrIn6_; // 28 bytes
};
