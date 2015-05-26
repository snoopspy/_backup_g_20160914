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

  GSockAddr(sa_family_t family) {
    addrIn_.sin_family = family;
  }

  GSockAddr(sa_family_t family, in_port_t port) {
    addrIn_.sin_family = family;
    addrIn_.sin_port = port;
  }

  GSockAddr(sa_family_t family, in_port_t port, in_addr_t addr) {
    addrIn_.sin_family = family;
    addrIn_.sin_port = port;
    addrIn_.sin_addr.s_addr = addr;
  }

  struct sockaddr addr_;
  struct sockaddr_in addrIn_;
  struct sockaddr_in6 addrIn6;
};
