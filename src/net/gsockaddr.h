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

#include <cstring>
#include <netinet/in.h>

// ----------------------------------------------------------------------------
// GSockAddr
// ----------------------------------------------------------------------------
union GSockAddr {
  GSockAddr() {}
  GSockAddr(sa_family_t family,
    in_port_t port,
    in_addr_t addr) {
    init(family, port, addr);
  }

  GSockAddr(sa_family_t family,
    in_port_t sin6_port,
    uint32_t sin6_flowinfo,
    struct in6_addr sin6_addr,
    uint32_t sin6_scope_id) {
    init(family, sin6_port, sin6_flowinfo, sin6_addr, sin6_scope_id);
  }

  void init(sa_family_t family,
    in_port_t port,
    in_addr_t addr) { // addrIn_
    addrIn_.sin_family = family;
    addrIn_.sin_port = port;
    addrIn_.sin_addr.s_addr = addr;
    memset(addrIn_.sin_zero, 0, sizeof(addrIn_.sin_zero));
  }

  void init(sa_family_t family,
    in_port_t sin6_port,
    uint32_t sin6_flowinfo,
    struct in6_addr sin6_addr,
    uint32_t sin6_scope_id) {
    addrIn6.sin6_family = family;
    addrIn6.sin6_port = sin6_port;
    addrIn6.sin6_flowinfo = sin6_flowinfo;
    addrIn6.sin6_addr = sin6_addr;
    addrIn6.sin6_scope_id = sin6_scope_id;
  }

  struct sockaddr addr_; // 16 bytes
  struct sockaddr_in addrIn_; // 16 bytes
  struct sockaddr_in6 addrIn6; // 28 bytes
};
