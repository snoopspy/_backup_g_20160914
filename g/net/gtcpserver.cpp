#include "gaddrinfo.h"
#include "gtcpserver.h"

// ----------------------------------------------------------------------------
// GTcpServer
// ----------------------------------------------------------------------------
GTcpServer::GTcpServer(GObj *parent) : GNetServer(parent) {
}

GTcpServer::~GTcpServer() {
  close();
}

bool GTcpServer::open() {
  if (port_ == 0) {
    SET_ERR(GNetErr(g::PORT_IS_ZERO, "port is zero"));
    return false;
  }
  if (!bind())
    return false;
  if (!listen())
    return false;
  return true;
}

bool GTcpServer::close() {
  return acceptClose();
}

bool GTcpServer::bind() {
  GAddrInfo addrInfo;
  memset(&addrInfo.hints_, 0, sizeof(struct addrinfo));
  addrInfo.hints_.ai_family = family_;
  addrInfo.hints_.ai_socktype = SOCK_STREAM;
  addrInfo.hints_.ai_flags = AI_PASSIVE;

  QString port = QString::number(port_);
  if (!addrInfo.query(qPrintable(localIp_), qPrintable(port), err))
    return false;

  bool succeed = false;
  for (struct addrinfo* info = addrInfo.infos_; info != nullptr; info = info->ai_next) {
    if (!acceptSock_.socket(info->ai_family, info->ai_socktype, info->ai_protocol)) {
      acceptSock_.close();
      continue;
    }

    if (nonBlock_) {
      if (!acceptSock_.setNonblock()) {
        acceptSock_.close();
       continue;
      }
    }

    if (!acceptSock_.setsockopt(SOL_SOCKET, SO_REUSEADDR)) {
      acceptSock_.close();
      continue;
    }

    if (!acceptSock_.bind(info->ai_addr, info->ai_addrlen)) {
      acceptSock_.close();
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

bool GTcpServer::listen() {
  return acceptSock_.listen(backLog_);
}

GSock GTcpServer::accept(GSockAddr *sockAddr, socklen_t *addrLen) {
  return acceptSock_.accept(sockAddr, addrLen);
}

bool GTcpServer::acceptClose() {
  if (acceptSock_ == -1)
    return true;
  bool res = true;
  if (!acceptSock_.shutdown())
    res = false;
  if (!acceptSock_.close())
    res = false;
  acceptSock_ = -1;
  return res;
}
