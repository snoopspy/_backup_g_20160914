#include <iostream>
#include <gflags/gflags.h>
#include <GErr>
#include <GSock>

DEFINE_bool(ip6, false, "use ipv6");
DEFINE_int32(port, 10065, "port number");
DEFINE_string(localHost, "", "local host");

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  GSock sock;
  GSockAddr sockAddr;
  if (!FLAGS_ip6) {
    // ip4
    sock.socket(AF_INET, SOCK_STREAM, 0);
    sockAddr.init(AF_INET, htons(FLAGS_port), INADDR_ANY);
    sock.bind(sockAddr, sizeof(struct sockaddr));
  } else {
    // ip6
    sock.socket(AF_INET6, SOCK_STREAM, 0);
    // gilgil temp
  }

}
