#include "gtcpclient.h"

// ----------------------------------------------------------------------------
// GTcpClient
// ----------------------------------------------------------------------------
GTcpClient::GTcpClient(GObj *parent) : GNetClient(parent) {
  tcpSession_ = new GTcpSession(this);
}

GTcpClient::~GTcpClient() {
  if (tcpSession_ != nullptr) {
    delete tcpSession_;
    tcpSession_ = nullptr;
  }
}

bool GTcpClient::open() {
  // gilgil temp 2015.06.08
  SET_ERR(GStdErr(g::NOT_SUPPORTED, "NOT_SUPPORTED"));
  return false;
}

bool GTcpClient::close() {
  // gilgil temp 2015.06.08
  SET_ERR(GStdErr(g::NOT_SUPPORTED, "NOT_SUPPORTED"));
  return false;
}
