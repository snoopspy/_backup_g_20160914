#include <net/gnetserver.h>

// ----------------------------------------------------------------------------
// GNetServer
// ----------------------------------------------------------------------------
bool GNetServer::checkLocalIpAndPort() {
  if (port_ == 0) {
    SET_ERR(GNetErr(g::PORT_NOT_SPECIFIED, "port not specified"));
    return false;
  }
  return true;
}

GSock GNetServer::bind() {
  return GNet::bind(sockType_, localIp_, port_, true);
}
