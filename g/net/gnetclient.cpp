#include "gnetclient.h"

// ----------------------------------------------------------------------------
// GNetClient
// ----------------------------------------------------------------------------
bool GNetClient::checkHostAndPort() {
  if (host_.isEmpty()) {
    SET_ERR(GNetErr(g::HOST_NOT_SPECIFIED, "host not specified"));
    return false;
  }

  if (port_.isEmpty() || port_ == "0") {
    SET_ERR(GNetErr(g::PORT_NOT_SPECIFIED, "port not specified"));
    return false;
  }
  return true;
}

GSock GNetClient::bind() {
  GSock sock = GNet::bind(sockType_, localIp_, localPort_, true);
  if (sock == INVALID_SOCKET) {
    GLastErr lastErr;
    SET_ERR(GNetErr(lastErr.code(), lastErr.msg()));
    return INVALID_SOCKET;
  }
  return sock;
}

bool GNetClient::connect(GSock sock) {
  if (!GNet::connect(sock, sockType_, host_, port_)) {
      GLastErr lastErr;
      SET_ERR(GNetErr(lastErr.code(), lastErr.msg()));
      return false;
  }
  return true;
}
