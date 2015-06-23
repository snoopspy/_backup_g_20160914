#include "gaddrinfo.h"
#include "gnetserver.h"

// ----------------------------------------------------------------------------
// GNetServer
// ----------------------------------------------------------------------------
bool GNetServer::checkLocalIpAndPort() {
  if (port_.isEmpty() || port_ == "0") {
    SET_ERR(GNetErr(g::PORT_NOT_SPECIFIED, "port not specified"));
    return false;
  }
  return true;
}

GSock GNetServer::bind() {
  return GNet::bind(localIp_, port_, true);
}

bool GNetServer::listen(GSock sock, int backLog) {
  if (!sock.listen(backLog)) {
    GLastErr lastErr;
    SET_ERR(GNetErr(lastErr.code(), QString("%1 backLoc=%2")
      .arg(lastErr.msg(), backLog)));
    return false;
  }
  return true;
}
