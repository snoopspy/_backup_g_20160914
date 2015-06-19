#include "gaddrinfo.h"
#include "gnet.h"

// ----------------------------------------------------------------------------
// GNet
// ----------------------------------------------------------------------------
GSock GNet::bind(int sockType, QString ip, QString port, bool reuseAddr) {
  GAddrInfo addrInfo;
  addrInfo.hints_.ai_family = family_;
  addrInfo.hints_.ai_socktype = sockType;
  addrInfo.hints_.ai_flags = AI_PASSIVE;

  if (!addrInfo.query(qPrintable(ip), qPrintable(port), &err)) {
    LOG(ERROR) << err;
    return GSock(INVALID_SOCKET);
  }

  GSock sock;
  bool succeed = false;
  for (struct addrinfo* info = addrInfo.infos_; info != nullptr; info = info->ai_next) {
    if (!sock.socket(info->ai_family, info->ai_socktype, info->ai_protocol)) {
      sock.close();
      continue;
    }

    if (nonBlock_) {
      if (!sock.setNonblock()) {
        sock.close();
       continue;
      }
    }

    if (reuseAddr) {
      if (!sock.setsockopt(SOL_SOCKET, SO_REUSEADDR)) {
        sock.close();
        continue;
      }
    }

    if (!sock.bind(info->ai_addr, info->ai_addrlen)) {
      sock.close();
      continue;
    }
    succeed = true;
    break;
  }

  if (!succeed) {
    GLastErr lastErr;
    SET_ERR(GNetErr(lastErr.code(), QString("%1 ip=%2 port=%3").arg(lastErr.msg(), ip, port)));
    return GSock(INVALID_SOCKET);
  }
  return sock;
}

bool GNet::connect(GSock sock, int sockType, QString host, QString port) {
  GAddrInfo addrInfo;
  addrInfo.hints_.ai_family = family_;
  addrInfo.hints_.ai_socktype = sockType;

  if (!addrInfo.query(qPrintable(host), qPrintable(port)), &err) {
    LOG(ERROR) << err << QString("host=%1 port=%2").arg(host, port);
    return false;
  }

  bool succeed = false;
  for (struct addrinfo* info = addrInfo.infos_; info != nullptr; info = info->ai_next) {
    if (!sock.connect(info->ai_addr, info->ai_addrlen)) {
      if (!(nonBlock_ && errno == EINPROGRESS)) {
        sock.close();
        continue;
      }
    }
    succeed = true;
    break;
  }

  if (!succeed) {
    GLastErr lastErr;
    SET_ERR(GNetErr(lastErr.code(), QString("%1 host=%2 port=%3").arg(lastErr.msg(), host, port)));
    return false;
  }
  return true;
}

bool GNet::listen(GSock sock, int backLog) {
  if (!sock.listen(backLog)) {
    GLastErr lastErr;
    SET_ERR(GNetErr(lastErr.code(), lastErr.msg()));
    return false;
  }
  return true;
}
