#include "gtcpclient.h"

// ----------------------------------------------------------------------------
// GTcpClient
// ----------------------------------------------------------------------------
GTcpClient::GTcpClient(GObj* parent) : GNetClient(parent) {
}

GTcpClient::~GTcpClient() {
  close();
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
    if (newSock == -1)
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
