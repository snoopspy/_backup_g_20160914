#include <arpa/inet.h>
#include "g/base/gerr.h"
#include "g/log/glog.h"
#include "gip.h"

// ----------------------------------------------------------------------------
// GIp
// ----------------------------------------------------------------------------
GIp& GIp::operator =(const char* p) {
  quint32 ui;
  int res = inet_pton(AF_INET, p, &ui);
  switch (res) {
    case 0:
      LOG(ERROR) << "inet_pton return zero ip=" << p;
      break;
    case 1: // succeed
      ip_ = ntohl(ui);
      break;
    default:
      LOG(ERROR) << "inet_pton return " << res << " " << GLastErr();
  }
  return *this;
}

GIp::operator QString() const {
  quint32 ui = htonl(ip_);
  char s[INET_ADDRSTRLEN];
  const char* res = inet_ntop(AF_INET, &ui, s, INET_ADDRSTRLEN);
  if (res == nullptr) {
    LOG(ERROR) << "inet_ntop return null " << GLastErr();
    return QString();
  }
  return QString{s};
}

// ----------------------------------------------------------------------------
// GTEST
// ----------------------------------------------------------------------------
#ifdef GTEST
#include <gtest/gtest.h>

TEST(GIp, ctorTest) {
  GIp ip1; // ()
  GIp ip2{ip1}; // (const GIp& rhs)
  GIp ip3{"127.0.0.1"}; // (const char* ip)
  GIp ip4{(QString)"127.0.0.1"}; // (const QString ip)
}

TEST(GIp, assignTest) {
  GIp ip1{"127.0.0.1"};
  GIp ip2;

  ip2 = ip1; // operator =(const GIp& rhs)
  EXPECT_EQ(ip2, 0x7F000001);

  ip2 = 0x7F000002; // operator =(const quint32 ip)
  EXPECT_EQ(ip2, 0x7F000002);

  ip2 = "127.0.0.3"; // operator =(const char* ip)
  EXPECT_EQ(ip2, 0x7F000003);

  ip2 = (QString)"127.0.0.4"; // operator =(const QString ip)
  EXPECT_EQ(ip2, 0x7F000004);
}

TEST(GIp, operatorTest) {
  GIp ip{"127.0.0.1"};

  quint32 ui; ui = ip; // operator quint32()
  EXPECT_EQ(ui, 0x7F000001);

  QString s1; s1 = (const char*)ip; //operator const char*()
  EXPECT_EQ(s1, "127.0.0.1");

  QString s2; s2 = (QString)ip; // operator QString()
  EXPECT_EQ(s2, "127.0.0.1");
}

TEST(GIp, funcTest) {
  GIp ip;

  ip = "127.0.0.1";
  EXPECT_TRUE(ip.isLocalHost());

  ip = "255.255.255.255";
  EXPECT_TRUE(ip.isBroadcast());

  ip = "224.0.0.0";
  EXPECT_TRUE(ip.isMulticast());
}

#endif // GTEST

