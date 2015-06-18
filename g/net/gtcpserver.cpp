#include "gtcpserver.h"

// ----------------------------------------------------------------------------
// GTcpServer
// ----------------------------------------------------------------------------
GTcpServer::GTcpServer(GObj* parent) : GNetServer(parent) {
  sockType_ = SOCK_STREAM;
  acceptSession_ = new GTcpSession(this);
}

GTcpServer::~GTcpServer() {
  close();
  if (acceptSession_ != nullptr) {
    delete acceptSession_;
    acceptSession_ = nullptr;
  }
}

bool GTcpServer::open() {
  if (!GNetServer::checkLocalIpAndPort())
    return false;

  acceptSession_->sock_ = GNetServer::bind();
  if (acceptSession_->sock_ == INVALID_SOCKET)
    return false;

  if (!GNetServer::listen(acceptSession_->sock_, backLog_))
    return false;

  return true;
}

bool GTcpServer::close() {
  bool res = acceptSession_->close();
  return res;
}

GTcpSession* GTcpServer::accept() {
  GSock newSock = acceptSession_->sock_.accept();
  if (newSock == INVALID_SOCKET)
    return nullptr;

  GTcpSession* newSession = new GTcpSession(this);
  newSession->sock_ = newSock;
  return newSession;
}

// ----------------------------------------------------------------------------
// GTEST
// ----------------------------------------------------------------------------
#ifdef GTEST
#include <gtest/gtest.h>

TEST(GTcpServer, openCloseTest) {
  GTcpServer tcpServer;
  tcpServer.port_ = "10065";
  for (int i = 0; i < 100000; i++) {
    EXPECT_TRUE(tcpServer.open());
    EXPECT_TRUE(tcpServer.close());
  }
}

#endif // GTEST
