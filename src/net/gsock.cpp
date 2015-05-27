#include <unistd.h> // for close
#include "gsock.h"
#include "base/gerr.h"

// ----------------------------------------------------------------------------
// GSock
// ----------------------------------------------------------------------------
GSock::GSock(int domain, int type, int protocol) {
  socket(domain, type, protocol);
}

int GSock::accept(GSockAddr *sockAddr, socklen_t *addrLen) {
  int res = ::accept((int)*this, &sockAddr->addr_, addrLen);
  if (res == -1)
    lastErr.set(errno);
  return res;
}

bool GSock::bind(GSockAddr* sockAddr, socklen_t addrLen) {
  int res = ::bind((int)*this, &sockAddr->addr_, addrLen);
  if (res == -1)
    lastErr.set(errno);
  return res != -1;
}

bool GSock::close() {
  int res = ::close((int)*this);
  if (res == -1)
    lastErr.set(errno);
  return res != -1;
}

bool GSock::listen(int backLog) {
  int res = ::listen((int)*this, backLog);
  if (res == -1)
    lastErr.set(errno);
  return res != -1;
}

ssize_t GSock::recv(void *buf, size_t len, int flags) {
  ssize_t res = ::recv((int)*this, buf, len, flags);
  if (res == -1)
    lastErr.set(errno);
  return res;
}

ssize_t GSock::recvfrom(void *buf, size_t len, int flags, GSockAddr* srcAddr, socklen_t *addrLen) {
  ssize_t res = ::recvfrom((int)*this, buf, len, flags, &srcAddr->addr_, addrLen);
  if (res == -1)
    lastErr.set(errno);
  return res;
}

ssize_t GSock::recvmsg(struct msghdr *msg, int flags) {
  ssize_t res = ::recvmsg((int)*this, msg, flags);
  if (res == -1)
    lastErr.set(errno);
  return res;
}

ssize_t GSock::send(const void *buf, size_t len, int flags) {
  ssize_t res = ::send((int)*this, buf, len, flags);
  if (res == -1)
    lastErr.set(errno);
  return res;
}

ssize_t GSock::sendto(const void *buf, size_t len, int flags, GSockAddr *destAddr, socklen_t addrLen) {
  ssize_t res = ::sendto((int)*this, buf, len, flags, &destAddr->addr_, addrLen);
  if (res == -1)
    lastErr.set(errno);
  return res;
}

ssize_t GSock::sendmsg(const struct msghdr *msg, int flags) {
  ssize_t res = ::sendmsg((int)*this, msg, flags);
  if (res == -1)
    lastErr.set(errno);
  return res;
}

bool GSock::setsockopt(int level, int optName, const void *optVal, socklen_t optLen) {
  int res = ::setsockopt((int)*this, level, optName, optVal, optLen);
  if (res == -1)
    lastErr.set(errno);
  return res != -1;
}

bool GSock::socket(int domain, int type, int protocol) {
  sock_ = ::socket(domain, type, protocol);
  if (sock_ == -1) {
    lastErr.set(errno);
  }
  return sock_ != -1;
}
