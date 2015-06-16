#include <sys/ioctl.h>
#include <netdb.h>
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
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = family_;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  QString port = QString::number(localPort_);
  struct addrinfo *infos;
  int res = getaddrinfo(
    localIp_.isEmpty() ? nullptr : qPrintable(localIp_),
    qPrintable(port),
    &hints,
    &infos);
  if (res != 0) {
    SET_ERR(GNetErr(res, gai_strerror(res)));
    return false;
  }

  bool succeed = false;
  for (struct addrinfo* info = infos; info != nullptr; info = info->ai_next) {
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
  freeaddrinfo(infos);

  if (!succeed) {
    GLastErr lastErr;
    SET_ERR(GNetErr(lastErr.code(), lastErr.msg()));
    return false;
  }
  return true;
}

bool GTcpClient::connect() {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = family_;
  hints.ai_socktype = SOCK_STREAM;

  QString port = QString::number(port_);
  struct addrinfo *infos;
  int res = getaddrinfo(
    qPrintable(host_),
    qPrintable(port),
    &hints,
    &infos);
  if (res != 0) {
    SET_ERR(GNetErr(res, gai_strerror(res)));
    return false;
  }

  bool succeed = false;
  for (struct addrinfo* info = infos; info != nullptr; info = info->ai_next) {
    if (!sock_.connect(info->ai_addr, info->ai_addrlen)) {
      if (!(nonBlock_ && errno == EINPROGRESS)) {
        sock_.close();
        continue;
      }
    }
    succeed = true;
    break;
  }
  freeaddrinfo(infos);

  if (!succeed) {
    GLastErr lastErr;
    SET_ERR(GNetErr(lastErr.code(), lastErr.msg()));
    return false;
  }
  return true;
}
