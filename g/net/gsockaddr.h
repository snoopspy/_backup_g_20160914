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

// ----------------------------------------------------------------------------
// GSockAddr
// ----------------------------------------------------------------------------
union GSockAddr {
  struct sockaddr addr_; // 16 bytes
  struct sockaddr_in addrIn_; // 16 bytes
  struct sockaddr_in6 addrIn6_; // 28 bytes
};
