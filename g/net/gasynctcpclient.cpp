#include "gasynctcpclient.h"

// ----------------------------------------------------------------------------
// GAsyncTcpClient
// ----------------------------------------------------------------------------
GAsyncTcpClient::GAsyncTcpClient(GObj* parent) : GTcpClient(parent) {
  nonBlock_ = true;
}

GAsyncTcpClient::~GAsyncTcpClient() {
  close();
}

bool GAsyncTcpClient::open() {
  if (!GTcpClient::open())
    return false;

  tcpSession_.sock_ = sock_;
  if (!tcpSession_.open())
    return false;

  return true;
}

bool GAsyncTcpClient::close() {
  bool res = true;

  if (!GTcpClient::close())
    res = false;

  if (!tcpSession_.close())
    res = false;

  return res;
}
