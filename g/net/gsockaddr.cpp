#include <assert.h>
#include <string.h>
#include "gaddrinfo.h"
#include "gsockaddr.h"

// ----------------------------------------------------------------------------
// GSockAddr
// ----------------------------------------------------------------------------
GSockAddr::GSockAddr() {
}

GSockAddr::GSockAddr(struct sockaddr* addr) {
  memcpy(this, addr, sizeof(*addr));
}

GSockAddr::GSockAddr(struct sockaddr_in* addrIn) {
  memcpy(this, addrIn, sizeof(*addrIn));
}

GSockAddr::GSockAddr(struct sockaddr_in6* addrIn6) {
  memcpy(this, addrIn6, sizeof(*addrIn6));
}

GErr* GSockAddr::init(const char* host, const char* port) {
  GAddrInfo addrInfo;
  GErr* err = addrInfo.query(host, port);
  if (err == nullptr) {
    assert(addrInfo.info_->ai_addrlen <= sizeof(*this));
    memcpy(this, addrInfo.info_->ai_addr, addrInfo.info_->ai_addrlen);
  }
  return err;
}

int GSockAddr::family() {
  return addr_.sa_family;
}

GIp GSockAddr::ip() {
  GIp res;
  if (addr_.sa_family != AF_INET) {
    res.clear();
    return res;
  }
  res = addrIn_.sin_addr;
  return res;
}

GIp6 GSockAddr::ip6() {
  GIp6 res;
  if (addr_.sa_family != AF_INET6) {
    res.clear();
    return res;
  }
  res = addrIn6_.sin6_addr;
  return res;
}

quint16 GSockAddr::port() {
  if (addr_.sa_family == AF_INET)
    return ntohs(addrIn_.sin_port);
  else if (addr_.sa_family == AF_INET6)
    return htons(addrIn6_.sin6_port);
  else
    return 0;
}

// ----------------------------------------------------------------------------
// GTEST
// ----------------------------------------------------------------------------
#ifdef GTEST
#include <gtest/gtest.h>

TEST(GSockAddr, ipTest) {
  GSockAddr sockAddr;
  EXPECT_EQ(sockAddr.init("127.0.0.1", nullptr), nullptr);
  EXPECT_EQ(sockAddr.family(), AF_INET);
  QString ip = (QString)(sockAddr.ip());
  EXPECT_EQ(ip, "127.0.0.1");
  quint16 port = sockAddr.port();
  EXPECT_EQ(port, 0);
}

TEST(GSockAddr, ip6Test) {
  GSockAddr sockAddr;
  EXPECT_EQ(sockAddr.init("::1", nullptr), nullptr);
  EXPECT_EQ(sockAddr.family(), AF_INET6);
  QString ip6 = (QString)(sockAddr.ip6());
  EXPECT_EQ(ip6, "::1");
  quint16 port = sockAddr.port();
  EXPECT_EQ(port, 0);
}

TEST(GSockAddr, portTest) {
  GSockAddr sockAddr;
  EXPECT_EQ(sockAddr.init(nullptr, "80"), nullptr);
  quint16 port = sockAddr.port();
  EXPECT_EQ(port, 80);
}

#endif // GTEST
