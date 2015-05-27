#include <iostream>
#include <gflags/gflags.h>
#include <GErr>
#include <GSock>

DEFINE_bool(ip6, false, "use ipv6");
DEFINE_int32(port, 10065, "port number");

int main() {
  GSock sock(AF_INET, SOCK_STREAM, 0);
  GSockAddr sockAddr;
  if (!sock.bind(sockAddr), sizeof(struct sockaddr)) {
    std::clog << lastErr << std::endl;
  }
}
