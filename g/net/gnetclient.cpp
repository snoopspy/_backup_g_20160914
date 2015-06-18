#include "gnetclient.h"

// ----------------------------------------------------------------------------
// GNetClient
// ----------------------------------------------------------------------------
GSock GNetClient::open() {
  if (host_.isEmpty()) {
    SET_ERR(GNetErr(g::HOST_NOT_SPECIFIED, "host not specified"));
    return false;
  }

  if (port_.isEmpty() || port_ == "0") {
    SET_ERR(GNetErr(g::PORT_NOT_SPECIFIED, "port not specified"));
    return GSock(INVALID_SOCKET);
  }

  GSock sock = bind(SOCK_STREAM, localIp_, localPort_, true);
  if (sock_ == -1)
    return GSock(INVALID_SOCKET);

  if (!connect(sock, SOCK_STREAM, host_, port_))
    return false;

  return true;
}

bool GNetClient::close(GSock sock) {
  if (sock_ == -1)
    return true;

  bool res = true;
  if (!sock_.shutdown())
    res = false;

  if (!sock_.close())
    res = false;

  sock_ = -1;
  return res;
}
