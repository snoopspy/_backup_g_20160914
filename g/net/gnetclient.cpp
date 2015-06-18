#include "gnetclient.h"

// ----------------------------------------------------------------------------
// GNetClient
// ----------------------------------------------------------------------------
GSock GNetClient::doOpen() {
  if (host_.isEmpty()) {
    SET_ERR(GNetErr(g::HOST_NOT_SPECIFIED, "host not specified"));
    return false;
  }

  if (port_.isEmpty() || port_ == "0") {
    SET_ERR(GNetErr(g::PORT_NOT_SPECIFIED, "port not specified"));
    return GSock(INVALID_SOCKET);
  }

  GSock sock = bind(SOCK_STREAM, localIp_, localPort_, true);
  if (sock == INVALID_SOCKET)
    return sock;

  if (!connect(sock, SOCK_STREAM, host_, port_)) {
    sock.close();
    return GSock(INVALID_SOCKET);
  }

  return true;
}

bool GNetClient::doClose(GSock sock) {
  if (sock == INVALID_SOCKET)
    return true;

  bool res = true;

  if (!sock.shutdown())
    res = false;

  if (!sock.close())
    res = false;

  return res;
}
