#include <arpa/inet.h>
#include "base/gerr.h"
#include "log/glog.h"
#include "gip.h"

#include <iostream>

// ----------------------------------------------------------------------------
// GIp
// ----------------------------------------------------------------------------
GIp::GIp(const QString s) {
  uint32_t ui;
  int res = inet_pton(AF_INET, qPrintable(s), &ui);
  switch (res) {
    case 0:
      LOG(ERROR) << "inet_pton return zero s=" << s;
      break;
    case 1:
      ip_ = ntohl(ui);
      return; // succeed
    default:
      LOG(ERROR) << "inet_pton return " << res << " " << GLastErr();
  }
}

GIp::operator QString() const {
  uint32_t ui = htonl(ip_);
  char s[INET_ADDRSTRLEN];
  const char* res = inet_ntop(AF_INET, &ui, s, INET_ADDRSTRLEN);
  if (res == nullptr) {
    LOG(ERROR) << "inet_ntop return null " << GLastErr();
  }
  return QString(s);
}

// ----------------------------------------------------------------------------
// GTEST
// ----------------------------------------------------------------------------
#ifdef GTEST
#include <gtest/gtest.h>

TEST(GIp, test) {
  GIp ip("127.0.0.1");
  EXPECT_EQ(ip, 0x7F000001);

  QString s = ip;
  EXPECT_EQ(s, "127.0.0.1");

  // ip = "abcdefg"; // gilgil temp 2015.06.04
}

#endif // GTEST
