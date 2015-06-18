#include <net/gnetserver.h>

// ----------------------------------------------------------------------------
// GNetServer
// ----------------------------------------------------------------------------
bool GNetServer::checkLocalIpAndPort() {
  if (port_ == 0) {
    SET_ERR(GNetErr(g::PORT_NOT_SPECIFIED, "port not specified"));
    false;
  }
  return true;
}

GSock GNetServer::bind() {
  GSock sock = GNet::bind(sockType_, localIp_, port_, true);
  if (sock == INVALID_SOCKET) {
    GLastErr lastErr;
    SET_ERR(GNetErr(lastErr.code(), lastErr.msg()));
    return INVALID_SOCKET;
  }
  return sock;
}
