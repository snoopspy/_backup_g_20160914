#include "gasynctcpclient.h"

// ----------------------------------------------------------------------------
// GAsyncTcpClient
// ----------------------------------------------------------------------------
GAsyncTcpClient::GAsyncTcpClient(GObj* parent) : GTcpClient(parent) {
  nonBlock_ = true;
  tcpSession_ = new GAsyncTcpSession(this);
}

// ----------------------------------------------------------------------------
// GTEST
// ----------------------------------------------------------------------------
#ifdef GTEST
#include <gtest/gtest.h>

TEST(GAsyncTcpClient, failTest) {
  GAsyncTcpClient tcpClient;
  tcpClient.host_ = "localhost";
  tcpClient.port_ = "10065";
  EXPECT_TRUE(tcpClient.open());
  EXPECT_FALSE(tcpClient.close());
}

#include <thread>
#include "gtcpserver.h"

static void acceptProc(GTcpServer* tcpServer) {
  while (true) {
    GTcpSession* newSession = tcpServer->accept();
    if (newSession == nullptr)
      break;
    delete newSession;
  }
}

TEST(GAsyncTcpClient, openCloseTest) {
  GTcpServer tcpServer;
  tcpServer.port_ = "10065";
  EXPECT_TRUE(tcpServer.open());
  std::thread acceptThread(acceptProc, &tcpServer);

  GAsyncTcpClient tcpClient;
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
