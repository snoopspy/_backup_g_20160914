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
  GSockAddr(sa_family_t family, in_port_t port, in_addr_t addr);

  void init(sa_family_t family, in_port_t port, in_addr_t addr);

  struct sockaddr addr_;
  struct sockaddr_in addrIn_;
  struct sockaddr_in6 addrIn6;
};
