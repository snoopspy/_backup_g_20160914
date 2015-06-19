#include <assert.h>
#include <string.h>
#include "gsockaddr.h"

// ----------------------------------------------------------------------------
// GSockAddr
// ----------------------------------------------------------------------------
GSockAddr::GSockAddr(struct sockaddr* addr) {
  memcpy(this, addr, sizeof(*addr));
}

GSockAddr::GSockAddr(struct sockaddr_in* addrIn) {
  memcpy(this, addrIn, sizeof(*addrIn));
}

GSockAddr::GSockAddr(struct sockaddr_in6* addrIn6) {
  memcpy(this, addrIn6, sizeof(*addrIn6));
}

int GSockAddr::family() {
  return addr_.sa_family;
}

GIp GSockAddr::ip() {
  GIp res;
  if (addr_.sa_family != AF_INET) {
    res.clear();
    return res;
  }
  res = addrIn_.sin_addr;
  return res;
}

GIp6 GSockAddr::ip6() {
  GIp6 res;
  if (addr_.sa_family != AF_INET6) {
    res.clear();
    return res;
  }
  res = addrIn6_.sin6_addr;
  return res;
}

quint16 GSockAddr::port() {
  if (addr_.sa_family == AF_INET)
    return ntohs(addrIn_.sin_port);
  else if (addr_.sa_family == AF_INET6)
    return htons(addrIn6_.sin6_port);
  else
    return 0;
}
