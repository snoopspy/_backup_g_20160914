#include "gaddrinfo.h"
#include "gnet.h"

// ----------------------------------------------------------------------------
// GNet
// ----------------------------------------------------------------------------
GSock GNet::bind(const QString& ip, const QString& port, bool reuseAddr) {
  GAddrInfo addrInfo;
  struct addrinfo hints;

  memset(&hints, 0, sizeof(hints));
  hints.ai_flags = AI_PASSIVE;
  hints.ai_family = family_;
  hints.ai_socktype = sockType_;

  err = addrInfo.query(hints, qPrintable(ip), qPrintable(port));
  if (err != nullptr) {
    LOG(ERROR) << err << QString(" host=%1 port=%2").arg(ip, port);
    return GSock(INVALID_SOCKET);
  }

  GSock sock;
  bool succeed = false;
  struct addrinfo* info = addrInfo.info_;
  while (true) {
    if (!sock.socket(info->ai_family, info->ai_socktype, info->ai_protocol)) {
      GLastErr lastErr;
      SET_ERR(GNetErr(lastErr.code(), QString("%1 family=%2 socktype=%3 protocol=%4")
        .arg(info->ai_family, info->ai_socktype, info->ai_protocol)));
      sock.close();
      break;
    }

    if (nonBlock_) {
      if (!sock.setNonblock()) {
        SET_ERR(GLastErr());
        sock.close();
        break;
      }
    }

    if (reuseAddr) {
      if (!sock.setsockopt(SOL_SOCKET, SO_REUSEADDR)) {
        SET_ERR(GLastErr());
        sock.close();
        break;
      }
    }

    if (!sock.bind(info->ai_addr, info->ai_addrlen)) {
      GLastErr lastErr;
      SET_ERR(GNetErr(lastErr.code(), QString("%1 ip=%2 port=%3")
        .arg(lastErr.msg(), ip, port)));
      sock.close();
      break;
    }

    succeed = true;
    break;
  }

  if (!succeed)
    return GSock(INVALID_SOCKET);
  return sock;
}

