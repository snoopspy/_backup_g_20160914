#include <netdb.h>
#include "gtcpserver.h"

// ----------------------------------------------------------------------------
// GTcpServerSession
// ----------------------------------------------------------------------------
struct GTcpServerSession : GTcpSession {
  GTcpServerSession(GTcpServer* tcpServer, GSock sock) :
    GTcpSession(sock), tcpServer_(tcpServer) {}

  ~GTcpServerSession() override {
    tcpServer_->tcpSessions_.remove(this);
  }

  GTcpServer* tcpServer_;
};

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
  acceptClose();
  for (GTcpSession* tcpSession: tcpSessions_) {
    tcpSession->close();
  }
  while (true) {
    if (tcpSessions_.size() == 0) break;
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
    SET_ERR(GNetErr(res, gai_strerror(res)));
    return false;
  }

  bool succeed = false;
  for (struct addrinfo* info = infos; info != nullptr; info = info->ai_next) {
    if (!acceptSock_.socket(info->ai_family, info->ai_socktype, info->ai_protocol)) {
      acceptSock_.close();
      continue;
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
  freeaddrinfo(infos);

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

GTcpSession* GTcpServer::accept(GSockAddr *sockAddr, socklen_t *addrLen) {
  GSock newSock = acceptSock_.accept(sockAddr, addrLen);
  if (newSock == -1)
    return nullptr;

  GTcpSession* newSession = new GTcpServerSession(this, newSock);
  tcpSessions_.insert(newSession);
  return newSession;
}

bool GTcpServer::acceptClose() {
  bool res = true;
  if (!acceptSock_.shutdown())
    res = false;
  if (!acceptSock_.close())
    res = false;
  acceptSock_ = -1;
  return res;
}
