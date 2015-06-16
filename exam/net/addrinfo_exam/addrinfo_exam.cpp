#include <gflags/gflags.h>
#include <netdb.h>
#include <iostream>
#include <string.h>
#include <unistd.h>

DEFINE_int32(family, AF_UNSPEC, "0:AF_UNSPEC 2:AF_INET 10:AF_INET6");
DEFINE_int32(socktype, SOCK_STREAM, "1:SOCK_STREAM 2:SOCK_DGRAM");
DEFINE_string(name, "", "name");
DEFINE_string(port, "10065", "port");

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = FLAGS_family; /* Allow IPv4 or IPv6 */
  hints.ai_socktype = FLAGS_socktype; /* Datagram socket */
  hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
  hints.ai_protocol = 0;          /* Any protocol */
  hints.ai_canonname = nullptr;
  hints.ai_addr = nullptr;
  hints.ai_next = nullptr;

  const char* name = FLAGS_name.empty() ? nullptr : FLAGS_name.c_str();
  struct addrinfo *result;
  int s = getaddrinfo(name, FLAGS_port.c_str(), &hints, &result);
  if (s != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    exit(EXIT_FAILURE);
  }

  int idx = 0;
  struct addrinfo* rp;
  for (rp = result; rp != nullptr; rp = rp->ai_next) {
    std::clog
      << "idx=" << idx
      << " family=" << rp->ai_family
      << " socktype=" << rp->ai_socktype
      << " protocol=" << rp->ai_protocol
      << std::endl;
    idx++;
  }

  idx = 0;
  for (rp = result; rp != nullptr; rp = rp->ai_next) {
    int sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (sfd == -1)
      continue;
    if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0) {
      std::clog << "success idx=" << idx << std::endl;
      break;
    }
    close(sfd);
  }
  if (rp == nullptr) {
    std::clog << "can not bind\n";
  }
}
