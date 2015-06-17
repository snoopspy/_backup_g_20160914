#include "gtcpclient.h"

// ----------------------------------------------------------------------------
// GTcpClient
// ----------------------------------------------------------------------------
GTcpClient::GTcpClient(GObj* parent) : GNetClient(parent) {
}

GTcpClient::~GTcpClient() {
  close();
}

bool GTcpClient::open() {
  if (host_.isEmpty()) {
    SET_ERR(GNetErr(g::HOST_NOT_SPECIFIED, "host not specified"));
    return false;
  }

  if (port_.isEmpty() || port_ == "0") {
    SET_ERR(GNetErr(g::PORT_NOT_SPECIFIED, "port not specified"));
    return false;
  }

  sock_ = bind(SOCK_STREAM, localIp_, localPort_, true);
  if (sock_ == -1)
    return false;

  if (!connect(sock_, SOCK_STREAM, host_, port_))
    return false;

  return true;
}

bool GTcpClient::close() {
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
