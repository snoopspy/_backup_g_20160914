#include "gtcpclient.h"

// ----------------------------------------------------------------------------
// GTcpClient
// ----------------------------------------------------------------------------
GTcpClient::GTcpClient(GObj* parent) : GNetClient(parent) {
  sockType_ = SOCK_STREAM;
  tcpSession_ = new GTcpSession(this);
}

GTcpClient::~GTcpClient() {
  close();
  if (tcpSession_ != nullptr) {
    delete tcpSession_;
    tcpSession_ = nullptr;
  }
}

bool GTcpClient::open() {
  if (!GNetClient::checkHostAndPort())
    return false;

  tcpSession_->sock_ = GNetClient::bind();
  if (tcpSession_->sock_ == INVALID_SOCKET)
    return false;

  if (!GNetClient::connect(tcpSession_->sock_))
    return false;

  return true;
}

bool GTcpClient::close() {
  bool res = tcpSession_->close();
  return res;
}

// ----------------------------------------------------------------------------
// GTEST
// ----------------------------------------------------------------------------
#ifdef GTEST
#include <gtest/gtest.h>

TEST(GTcpClient, failTest) {
  GTcpClient tcpClient;
  tcpClient.host_ = "localhost";
  tcpClient.port_ = "10065";
  EXPECT_FALSE(tcpClient.open());
  EXPECT_FALSE(tcpClient.close());
}

#include <thread>
#include "gtcpserver.h"

static void acceptProc(GTcpServer* tcpServer) {
  while (true) {
    GSock newSock = tcpServer->accept();
    if (newSock == INVALID_SOCKET)
      break;
    newSock.close();
  }
}

TEST(GTcpClient, openCloseTest) {
  GTcpServer tcpServer;
  tcpServer.port_ = "10065";
  EXPECT_TRUE(tcpServer.open());
  std::thread acceptThread(acceptProc, &tcpServer);

  GTcpClient tcpClient;
  tcpClient.host_ = "localhost";
  tcpClient.port_ = "10065";
  for (int i = 0; i < 10000; i++) {
    EXPECT_TRUE(tcpClient.open());
    EXPECT_TRUE(tcpClient.close());
    if (i % 100 == 0)
      std::clog << i << std::endl;
  }

  tcpServer.close();
  acceptThread.join();
}

#endif // GTEST
