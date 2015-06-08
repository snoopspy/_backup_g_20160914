#include "gtcpclient.h"

// ----------------------------------------------------------------------------
// GTcpClient
// ----------------------------------------------------------------------------
GTcpClient::GTcpClient(GObj *parent) : GNetClient(parent) {
  tcpSession = new GTcpSession(this);
}

GTcpClient::~GTcpClient() {
  if (tcpSession != nullptr) {
    delete tcpSession;
    tcpSession = nullptr;
  }
}

bool GTcpClient::open() {
  // gilgil temp 2015.06.08
  err = new GStdErr(g::NOT_SUPPORTED, "NOT_SUPPORTED");
  return false;
}

bool GTcpClient::close() {
  err = new GStdErr(g::NOT_SUPPORTED, "NOT_SUPPORTED");
  return false;
}
