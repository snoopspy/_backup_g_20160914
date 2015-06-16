#include "gaddrinfo.h"
#include "gtcpclient.h"

// ----------------------------------------------------------------------------
// GTcpClient
// ----------------------------------------------------------------------------
GTcpClient::GTcpClient(GObj *parent) : GNetClient(parent) {
}

GTcpClient::~GTcpClient() {
  close();
}

bool GTcpClient::open() {
  if (port_ == 0) {
    SET_ERR(GNetErr(g::PORT_IS_ZERO, "port is zero"));
    return false;
  }
  if (!bind())
    return false;
  if (!connect())
    return false;
  return true;
}

bool GTcpClient::close() {
  return sock_.close();
}

bool GTcpClient::bind() {
  GAddrInfo addrInfo;
  memset(&addrInfo.hints_, 0, sizeof(struct addrinfo));
  addrInfo.hints_.ai_family = family_;
  addrInfo.hints_.ai_socktype = SOCK_STREAM;
  addrInfo.hints_.ai_flags = AI_PASSIVE;

  QString port = QString::number(localPort_);
  if (!addrInfo.query(qPrintable(localIp_), qPrintable(port), err))
    return false;

  bool succeed = false;
  for (struct addrinfo* info = addrInfo.infos_; info != nullptr; info = info->ai_next) {
    if (!sock_.socket(info->ai_family, info->ai_socktype, info->ai_protocol)) {
      sock_.close();
      continue;
    }

    if (nonBlock_) {
      if (!sock_.setNonblock()) {
        sock_.close();
       continue;
      }
    }

    if (!sock_.setsockopt(SOL_SOCKET, SO_REUSEADDR)) {
      sock_.close();
      continue;
    }

    if (!sock_.bind(info->ai_addr, info->ai_addrlen)) {
      sock_.close();
      continue;
    }
    succeed = true;
    break;
  }

  if (!succeed) {
    GLastErr lastErr;
    SET_ERR(GNetErr(lastErr.code(), lastErr.msg()));
    return false;
  }
  return true;
}

bool GTcpClient::connect() {
  GAddrInfo addrInfo;
  memset(&addrInfo.hints_, 0, sizeof(struct addrinfo));
  addrInfo.hints_.ai_family = family_;
  addrInfo.hints_.ai_socktype = SOCK_STREAM;

  QString port = QString::number(port_);
  if (!addrInfo.query(qPrintable(host_), qPrintable(port), err))
    return false;

  bool succeed = false;
  for (struct addrinfo* info = addrInfo.infos_; info != nullptr; info = info->ai_next) {
    if (!sock_.connect(info->ai_addr, info->ai_addrlen)) {
      if (!(nonBlock_ && errno == EINPROGRESS)) {
        sock_.close();
        continue;
      }
    }
    succeed = true;
    break;
  }

  if (!succeed) {
    GLastErr lastErr;
    SET_ERR(GNetErr(lastErr.code(), lastErr.msg()));
    return false;
  }
  return true;
}
