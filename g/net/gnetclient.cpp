#include "gaddrinfo.h"
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
  return GNet::bind(localIp_, localPort_, true);
}

bool GNetClient::connect(GSock sock) {
  GAddrInfo addrInfo;
  struct addrinfo hints;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = family_;
  hints.ai_socktype = sockType_;

  err = addrInfo.query(hints, qPrintable(host_), qPrintable(port_));
  if (err != nullptr) {
    LOG(ERROR) << err << QString(" host=%1 port=%2").arg(host_, port_);
    return false;
  }

  bool succeed = false;
  struct addrinfo* info = addrInfo.info_;
  while (true) {
    if (!sock.connect(info->ai_addr, info->ai_addrlen)) {
      if (!(nonBlock_ && errno == EINPROGRESS)) {
        GLastErr lastErr;
        SET_ERR(GNetErr(lastErr.code(), QString("%1 host=%2 port=%3")
          .arg(lastErr.msg(), host_, port_)));
        sock.close();
        break;
      }
    }

    succeed = true;
    break;
  }

  if (!succeed) {
    return false;
  }
  return true;
}
