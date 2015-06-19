#include "gaddrinfo.h"
#include "gnet.h"

// ----------------------------------------------------------------------------
// GAddrInfo
// ----------------------------------------------------------------------------
bool GAddrInfo::query(const char* host, GErr** err) {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  return query(hints, host, nullptr, err);
}

bool GAddrInfo::query(const char* host, const char* port, GErr** err) {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  return query(hints, host, port, err);
}

bool GAddrInfo::query(const struct addrinfo& hints, const char* host, GErr** err) {
  return query(hints, host, nullptr, err);
}

bool GAddrInfo::query(const struct addrinfo& hints, const char* host, const char* port, GErr** err) {
  if (host != nullptr && *host == '\0')
    host = nullptr;

  if (port != nullptr && *port == '\0')
    port = nullptr;

  int res = getaddrinfo(host, port, &hints, &info_);
  if (res != 0 && err != nullptr) {
    *err = new GNetErr(res, gai_strerror(res));
    return false;
  }
  return true;
}
