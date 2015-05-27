#include <cstring>
#include "gsockaddr.h"

// ----------------------------------------------------------------------------
// GSockAddr
// ----------------------------------------------------------------------------
GSockAddr::GSockAddr(sa_family_t family, in_port_t port, in_addr_t addr) {
  init(family, port, addr);
}

void GSockAddr::init(sa_family_t family, in_port_t port, in_addr_t addr) {
  addrIn_.sin_family = family;
  addrIn_.sin_port = port;
  addrIn_.sin_addr.s_addr = addr;
  memset(addrIn_.sin_zero, 0, sizeof(addrIn_.sin_zero));
}
