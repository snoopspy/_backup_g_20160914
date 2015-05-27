#include "gsock.h"
#include "base/gerr.h"

// ----------------------------------------------------------------------------
// GSock
// ----------------------------------------------------------------------------
GSock::GSock(int domain, int type, int protocol) {
  socket(domain, type, protocol);
}

bool GSock::bind(GSockAddr& sockAddr, socklen_t addrlen) {
  int res = ::bind((int)*this, &sockAddr.addr_, addrlen);
  if (res != 0)
    lastErr.set(errno);
  return res == 0;
}

bool GSock::setsockopt(int level, int optname, const void *optval, socklen_t optlen) {
  int res = ::setsockopt((int)*this, level, optname, optval, optlen);
  if (res != 0)
    lastErr.set(errno);
  return res == 0;
}

bool GSock::socket(int domain, int type, int protocol) {
  sock_ = socket(domain, type, protocol);
  if (sock_ == -1) {
    lastErr.set(errno);
  }
  return sock_ != -1;
}
