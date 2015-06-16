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
  if (host_.isEmpty()) {
    SET_ERR(GNetErr(g::HOST_NOT_SPECIFIED, "host not specified"));
    return false;
  }
  if (port_.isEmpty() || port_ == "0") {
    SET_ERR(GNetErr(g::PORT_NOT_SPECIFIED, "port not specified"));
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
  addrInfo.hints_.ai_family = family_;
  addrInfo.hints_.ai_socktype = SOCK_STREAM;
  addrInfo.hints_.ai_flags = AI_PASSIVE;

  err = addrInfo.query(localIp_, localPort_);
  if (err != nullptr) {
    LOG(ERROR) << err;
    return false;
  }

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
    SET_ERR(GNetErr(lastErr.code(), QString("%1 localIp=%2 localPort=%3").arg(lastErr.msg(), localIp_).arg(localPort_)));
    return false;
  }
  return true;
}

bool GTcpClient::connect() {
  GAddrInfo addrInfo;
  addrInfo.hints_.ai_family = family_;
  addrInfo.hints_.ai_socktype = SOCK_STREAM;

  err = addrInfo.query(host_, port_);
  if (err != nullptr) {
    LOG(ERROR) << err;
    return false;
  }

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
    SET_ERR(GNetErr(lastErr.code(), QString("%1 host=%2 port=%3").arg(lastErr.msg(), host_).arg(port_)));
    return false;
  }
  return true;
}
