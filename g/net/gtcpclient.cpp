#include "gtcpclient.h"

// ----------------------------------------------------------------------------
// GTcpClient
// ----------------------------------------------------------------------------
GTcpClient::GTcpClient(GObj* parent) : GNetClient(parent) {
}

GTcpClient::~GTcpClient() {
  close();
}

bool GTcpClient::open() {
  if (host_.isEmpty()) {
    SET_ERR(GNetErr(g::HOST_NOT_SPECIFIED, "host not specified"));
    return false;
  }

  if (port_.isEmpty() || port_ == "0") {
    SET_ERR(GNetErr(g::PORT_NOT_SPECIFIED, "port not specified"));
    return false;
  }

  sock_ = bind(SOCK_STREAM, localIp_, localPort_, true);
  if (sock_ == -1)
    return false;

  if (!connect(sock_, SOCK_STREAM, host_, port_))
    return false;

  return true;
}

bool GTcpClient::close() {
  if (sock_ == -1)
    return true;

  bool res = true;
  if (!sock_.shutdown())
    res = false;

  if (!sock_.close())
    res = false;

  sock_ = -1;
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
