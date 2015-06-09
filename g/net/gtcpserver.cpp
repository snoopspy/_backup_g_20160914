#include <netdb.h>
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
    err = new GNetErr(g::PORT_IS_ZERO, "port is zero");
    return false;
  }
  if (!bind())
    return false;
  if (!listen())
    return false;
  return true;
}

bool GTcpServer::close() {
  acceptClose();
  for (GTcpSession* tcpSession: tcpSessions_) {
    delete tcpSession;
  }
  return true;
}

bool GTcpServer::bind() {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = family_;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  QString port = QString::number(port_);
  struct addrinfo *infos;
  int res = getaddrinfo(
    localIp_.isEmpty() ? nullptr : qPrintable(localIp_),
    qPrintable(port),
    &hints,
    &infos);
  if (res != 0) {
    err = new GStdErr(res, gai_strerror(res));
    return false;
  }

  bool succeed = false;
  for (struct addrinfo* info = infos; info != nullptr; info = info->ai_next) {
    if (!acceptSock_.socket(info->ai_family, info->ai_socktype, info->ai_protocol))
      continue;
    if (!acceptSock_.bind(info->ai_addr, info->ai_addrlen))
      continue;
    succeed = true;
    break;
  }
  freeaddrinfo(infos);

  if (!succeed) {
    GLastErr lastErr;
    err = new GNetErr(lastErr.code(), lastErr.msg());
    return false;
  }
  return true;
}

bool GTcpServer::listen() {
  return acceptSock_.listen(backLog_);
}

GSock GTcpServer::accept(GSockAddr *sockAddr, socklen_t *addrLen) {
  GSock newSock = acceptSock_.accept(sockAddr, addrLen);
  return newSock;
}

bool GTcpServer::acceptClose() {
  DLOG(INFO) << "bef acceptSock_.close()"; // gilgil temp
  bool res = acceptSock_.close();
  DLOG(INFO) << "aft acceptSock_.close()" << res; // gilgil temp
  return res;
}
