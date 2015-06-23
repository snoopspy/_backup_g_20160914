#include "gaddrinfo.h"
#include "gnet.h"

// ----------------------------------------------------------------------------
// GAddrInfo
// ----------------------------------------------------------------------------
GAddrInfo::GAddrInfo() : info_(nullptr) {
}

GAddrInfo::~GAddrInfo() {
  if (info_ != nullptr) {
    freeaddrinfo(info_);
    info_ = nullptr;
  }
}

GErr* GAddrInfo::query(const char* host) {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  return query(hints, host, nullptr);
}

GErr* GAddrInfo::query(const char* host, const char* port) {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  return query(hints, host, port);
}

GErr* GAddrInfo::query(const struct addrinfo& hints, const char* host) {
  return query(hints, host, nullptr);
}

GErr* GAddrInfo::query(const struct addrinfo& hints, const char* host, const char* port) {
  if (host != nullptr && *host == '\0')
    host = nullptr;

  if (port != nullptr && *port == '\0')
    port = nullptr;

  int res = getaddrinfo(host, port, &hints, &info_);
  if (res != 0) {
    info_  = nullptr;
    GErr* err = new GNetErr(res, gai_strerror(res));
    return err;
  }
  return nullptr;
}

// ----------------------------------------------------------------------------
// GTEST
// ----------------------------------------------------------------------------
#ifdef GTEST
#include <gtest/gtest.h>

TEST(GAddrInfo, ipTest) {
  GAddrInfo addrInfo;
  EXPECT_EQ(addrInfo.query("127.0.0.1"), nullptr);
  GSockAddr* sockAddr = (GSockAddr*)addrInfo.info_->ai_addr;
  EXPECT_EQ(sockAddr->family(), AF_INET);
  QString ip = (QString)(sockAddr->ip());
  EXPECT_EQ(ip, "127.0.0.1");
  quint16 port = sockAddr->port();
  EXPECT_EQ(port, 0);
}

TEST(GAddrInfo, ip6Test) {
  GAddrInfo addrInfo;
  EXPECT_EQ(addrInfo.query("::1"), nullptr);
  GSockAddr* sockAddr = (GSockAddr*)addrInfo.info_->ai_addr;
  EXPECT_EQ(sockAddr->family(), AF_INET6);
  QString ip6 = (QString)(sockAddr->ip6());
  EXPECT_EQ(ip6, "::1");
  quint16 port = sockAddr->port();
  EXPECT_EQ(port, 0);
}

TEST(GAddrInfo, portTest) {
  GAddrInfo addrInfo;
  EXPECT_EQ(addrInfo.query(nullptr, "80"), nullptr);
  GSockAddr* sockAddr = (GSockAddr*)addrInfo.info_->ai_addr;
  quint16 port = sockAddr->port();
  EXPECT_EQ(port, 80);
}
#endif // GTEST
