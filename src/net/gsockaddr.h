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
  GSockAddr() {}
  GSockAddr(sa_family_t family, in_port_t port, in_addr_t addr); // addrIn_

  void init(sa_family_t family, in_port_t port, in_addr_t addr); // addrIn_

  struct sockaddr addr_; // 16 bytes
  struct sockaddr_in addrIn_; // 16 bytes
  struct sockaddr_in6 addrIn6;
};
