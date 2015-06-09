#include <arpa/inet.h>
#include "g/base/gerr.h"
#include "g/log/glog.h"
#include "gip.h"

// ----------------------------------------------------------------------------
// GIp
// ----------------------------------------------------------------------------
GIp::GIp(QString s) {
  operator =(s);
}

GIp& GIp::operator = (QString s) {
  quint32 ui;
  int res = inet_pton(AF_INET, qPrintable(s), &ui);
  switch (res) {
    case 0:
      LOG(ERROR) << "inet_pton return zero s=" << s;
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
  GIp ip3{"127.0.0.1"}; // (const QString s)
}

TEST(GIp, assignTest) {
  GIp ip1{"127.0.0.1"};
  EXPECT_EQ(ip1, 0x7F000001);

  GIp ip2; ip2 = ip1; // operator = (const GIp& rhs)
  EXPECT_EQ(ip2, 0x7F000001);

  GIp ip3; ip3 = 0x7F000001; // operator = (const quint32 ip)
  EXPECT_EQ(ip3, 0x7F000001);

  GIp ip4; ip4 = "127.0.0.1"; // operator = (const QString s)
  EXPECT_EQ(ip4, 0x7F000001);
}

TEST(GIp, operatorTest) {
  GIp ip{"127.0.0.1"};
  quint32 ui; ui = ip; // quint32()
  EXPECT_EQ(ui, 0x7F000001);

  QString s; s = (QString)ip; // QString()
  EXPECT_EQ(s, "127.0.0.1");
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

