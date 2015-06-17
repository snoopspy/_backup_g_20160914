#include "gtcpserver.h"

// ----------------------------------------------------------------------------
// GTcpServer
// ----------------------------------------------------------------------------
GTcpServer::GTcpServer(GObj* parent) : GNetServer(parent) {
}

GTcpServer::~GTcpServer() {
  close();
}

bool GTcpServer::open() {
  if (port_ == 0) {
    SET_ERR(GNetErr(g::PORT_NOT_SPECIFIED, "port not specified"));
    return false;
  }

  acceptSock_ = bind(SOCK_STREAM, localIp_, port_, true);
  if (acceptSock_ == -1)
    return false;

  if (!listen())
    return false;

  return true;
}

bool GTcpServer::close() {
  return acceptClose();
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
