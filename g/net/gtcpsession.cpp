#include "gtcpsession.h"

// ----------------------------------------------------------------------------
// GTcpSession
// ----------------------------------------------------------------------------
ssize_t GTcpSession::read(char *buf, ssize_t len) {
  return sock_.recv(buf, len);
}

ssize_t GTcpSession::write(const char *buf, ssize_t len) {
  return sock_.send(buf, len);
}
