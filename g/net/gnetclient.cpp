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
  return GNet::bind(sockType_, localIp_, localPort_, true);
}

bool GNetClient::connect(GSock sock) {
  return GNet::connect(sock, sockType_, host_, port_);
}
