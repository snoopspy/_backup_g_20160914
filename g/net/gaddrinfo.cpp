#include "gaddrinfo.h"
#include "gnet.h"

// ----------------------------------------------------------------------------
// GAddrInfo
// ----------------------------------------------------------------------------
GErr* GAddrInfo::query(const char* host, const char* port) {
  if (host != nullptr && *host == '\0')
    host = nullptr;

  if (port != nullptr && *port == '\0')
    port = nullptr;

  int res = getaddrinfo(host, port, &hints_, &infos_);
  if (res != 0) {
    return new GNetErr(res, gai_strerror(res));
  }
  return nullptr;
}
