#include "gobj.h"

GObj::~GObj() {
  if (err != nullptr) {
    delete err;
    err = nullptr;
  }
}

bool GObj::open() {
  SET_ERR(GStdErr(g::VIRTUAL_FUNCTION_CALL, "virtual function call"));
  return false;
}

bool GObj::close() {
  SET_ERR(GStdErr(g::VIRTUAL_FUNCTION_CALL, "virtual function call"));
  return false;
}

// ----------------------------------------------------------------------------
// GTEST
// ----------------------------------------------------------------------------
#ifdef GTEST
#include <gtest/gtest.h>

#include <GTcpClient>
TEST(GObj, helpCommandLineTest) {
  GTcpClient tcpClient;
  tcpClient.helpCommandLine();
}

TEST(GObj, parseCommandLineTest) {
  GTcpClient tcpClient;
  const char* argv[] { "gtest", "-family=2", "-host=192.168.10.1", "-port=80", "-nonBlock=true" };
  tcpClient.parseCommandLine(5, argv);
  EXPECT_EQ(tcpClient.family_, AF_INET); // 2
  EXPECT_EQ(tcpClient.host_, "192.168.10.1");
  EXPECT_EQ(tcpClient.port_, "80");
  EXPECT_EQ(tcpClient.nonBlock_, true);
}

#endif // GTEST
