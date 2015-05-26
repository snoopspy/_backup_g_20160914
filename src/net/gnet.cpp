#include "gnet.h"

// ----------------------------------------------------------------------------
// GNet
// ----------------------------------------------------------------------------
int GNet::bind(GSock sock, GSockAddr& sockAddr, socklen_t len) {
  int res = ::bind((int)sock, &sockAddr.addr_, len);
  if (res == -1)
    lastErr.set(errno);
  return res;
}
