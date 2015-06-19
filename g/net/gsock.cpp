#include <unistd.h> // for close
#include <sys/ioctl.h> // for ioctl
#include "gsock.h"

// ----------------------------------------------------------------------------
// GSock
// ----------------------------------------------------------------------------
int GSock::accept(GSockAddr *sockAddr, socklen_t *addrLen) {
  int res = ::accept(sock_, (struct sockaddr*)sockAddr, addrLen);
  return res;
}

bool GSock::bind(struct sockaddr* sockAddr, socklen_t addrLen) {
  int res = ::bind(sock_, sockAddr, addrLen);
  return res == 0;
}

bool GSock::bind(GSockAddr* sockAddr, socklen_t addrLen) {
  int res = ::bind(sock_, &sockAddr->addr_, addrLen);
  return res == 0;
}

bool GSock::close() {
  int res = ::close(sock_);
  return res == 0;
}

bool GSock::connect(struct sockaddr* sockAddr, socklen_t addrLen) {
  int res = ::connect(sock_, sockAddr, addrLen);
  return res == 0;
}

bool GSock::connect(GSockAddr* sockAddr, socklen_t addrLen) {
  int res = ::connect(sock_, &sockAddr->addr_, addrLen);
  return res == 0;
}

bool GSock::listen(int backLog) {
  int res = ::listen(sock_, backLog);
  return res == 0;
}

ssize_t GSock::recv(void *buf, size_t len, int flags) {
  ssize_t res = ::recv(sock_, buf, len, flags);
  return res;
}

ssize_t GSock::recvfrom(void *buf, size_t len, int flags, GSockAddr* srcAddr, socklen_t *addrLen) {
  ssize_t res = ::recvfrom(sock_, buf, len, flags, &srcAddr->addr_, addrLen);
  return res;
}

ssize_t GSock::recvmsg(struct msghdr *msg, int flags) {
  ssize_t res = ::recvmsg(sock_, msg, flags);
  return res;
}

ssize_t GSock::send(const void *buf, size_t len, int flags) {
  ssize_t res = ::send(sock_, buf, len, flags);
  return res;
}

ssize_t GSock::sendto(const void *buf, size_t len, int flags, GSockAddr *destAddr, socklen_t addrLen) {
  ssize_t res = ::sendto(sock_, buf, len, flags, &destAddr->addr_, addrLen);
  return res;
}

ssize_t GSock::sendmsg(const struct msghdr *msg, int flags) {
  ssize_t res = ::sendmsg(sock_, msg, flags);
  return res;
}

bool GSock::setsockopt(int level, int optName, const void *optVal, socklen_t opeLen) {
  if (optVal == nullptr) {
    int temp = 1;
    int res = ::setsockopt(sock_, level, optName, &temp, sizeof(temp));
    return res == 0;
  }
  int res = ::setsockopt(sock_, level, optName, optVal, opeLen) != -1;
  return res == 0;
}

bool GSock::socket(int domain, int type, int protocol) {
  sock_ = ::socket(domain, type, protocol);
  return sock_ != INVALID_SOCKET;
}

bool GSock::shutdown(int how) {
  int res = ::shutdown(sock_, how);
  return res == 0;
}

bool GSock::setNonblock() {
  int i = 1;
  int res = ioctl(sock_, FIONBIO, &i);
  return res == 0;
}
