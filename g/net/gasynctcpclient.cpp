#include "gasynctcpclient.h"

// ----------------------------------------------------------------------------
// GAsyncTcpClient
// ----------------------------------------------------------------------------
GAsyncTcpClient::GAsyncTcpClient(GObj* parent) : GTcpClient(parent) {
  nonBlock_ = true;
}

GAsyncTcpClient::~GAsyncTcpClient() {
  close();
}

bool GAsyncTcpClient::open() {
  if (!GTcpClient::open())
    return false;

  tcpSession_.sock_ = sock_;
  if (!tcpSession_.open())
    return false;

  return true;
}

bool GAsyncTcpClient::close() {
  bool res = true;

  if (!GTcpClient::close())
    res = false;

  if (!tcpSession_.close())
    res = false;

  return res;
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
    GSock newSock = tcpServer->accept();
    if (newSock == -1)
      break;
    newSock.close();
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
