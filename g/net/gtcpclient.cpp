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
  bool ip4 = !ip6_;

  if (ip4) {
    if (!tcpSession_->sock_.socket(AF_INET, SOCK_STREAM, 0)) { err = new GLastErr(); return false; }
  } else {
    if (!tcpSession_->sock_.socket(AF_INET6, SOCK_STREAM, 0)) { err = new GLastErr(); return false; }
  }

  GSockAddr bindAddr;
  if (ip4) {
    bindAddr.init(AF_INET, htons(localPort_), htonl(localIp_));
  } else {
    bindAddr.init(AF_INET6, htons(localPort), 0, in6addr_any, 0);
  }
  if (!sock.bind(&bindAddr)) { LOG(ERROR) << GLastErr(); return; }



  // gilgil temp 2015.06.08
  return false;
}

bool GTcpClient::close() {
  // gilgil temp 2015.06.08
  return false;
}
