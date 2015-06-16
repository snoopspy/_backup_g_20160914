#include "gaddrinfo.h"
#include "gnet.h"

// ----------------------------------------------------------------------------
// GAddrInfo
// ----------------------------------------------------------------------------
GAddrInfo::~GAddrInfo() {
  if (infos_ != nullptr) {
    freeaddrinfo(infos_);
  }
}

bool GAddrInfo::query(const char* host, const char* port, GErr* err) {
  if (host != nullptr && *host == '\0')
    host = nullptr;
  int res = getaddrinfo(
    host,
    port,
    &hints_,
    &infos_);
  if (res != 0) {
    SET_ERR(GNetErr(res, gai_strerror(res)));
    return false;
  }
  return true;
}
