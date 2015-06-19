#include <arpa/inet.h> // for inet_ntop
#include <gflags/gflags.h>
#include <iostream>
#include <GAddrInfo>
#include <GIp>
#include <GIp6>
#include <GStr>
#include <GSockAddr>

DEFINE_int32(family, AF_UNSPEC, "0:AF_UNSPEC 2:AF_INET 10:AF_INET6");
DEFINE_int32(socktype, 0, "0:UNKNOWN 1:SOCK_STREAM 2:SOCK_DGRAM");
DEFINE_int32(flags, 0, "1:AI_PASSIVE");
DEFINE_string(host, "", "host");
DEFINE_string(port, "0", "port");

using namespace std;

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  GAddrInfo addrInfo;
  addrInfo.hints_.ai_family = FLAGS_family;
  addrInfo.hints_.ai_socktype = FLAGS_socktype;
  addrInfo.hints_.ai_flags = FLAGS_flags;

  GErr* err = addrInfo.query(FLAGS_host.c_str(), FLAGS_port.c_str());
  if (err != nullptr) {
    clog << err << endl;
    return EXIT_FAILURE;
  }

  clog << "idx\tfamily\t\tsocktype\tprotocol\tip(port)\n";
  int idx = 0;
  struct addrinfo* info;
  for (info = addrInfo.infos_; info != nullptr; info = info->ai_next) {
    clog << idx;

    clog  << "\t" << info->ai_family;
    switch (info->ai_family) {
      case AF_UNSPEC: clog << "(AF_UNSPEC)"; break;
      case AF_INET: clog << "(AF_INET)"; break;
      case AF_INET6: clog << "(AF_INET6)"; break;
    }

    clog << "\t" << info->ai_socktype;
    switch (info->ai_socktype) {
      case SOCK_STREAM: clog << "(SOCK_STREAM)"; break;
      case SOCK_DGRAM: clog << "(SOCK_DGRAM)"; break;
      case SOCK_RAW: clog << "(SOCK_RAW)"; break;
    }

    clog << "\t" << info->ai_protocol;
    switch (info->ai_protocol) {
      case IPPROTO_TCP: clog << "(IPPROTO_TCP)"; break;
      case IPPROTO_UDP: clog << "(IPPROTO_UDP)"; break;
      case IPPROTO_IP: clog << "(IPPROTO_IP)"; break;
    }

    GSockAddr* sockAddr = (GSockAddr*)info->ai_addr;
    if (info->ai_family == AF_INET) {
      GIp ip{sockAddr->addrIn_.sin_addr};
      clog << "\t" << QString(ip);
      clog << "(" << htons(sockAddr->addrIn_.sin_port) << ")";
      clog << endl;
    } else
   if (info->ai_family == AF_INET6) {
      GIp6 ip6{sockAddr->addrIn6_.sin6_addr};
      clog << "\t" << QString(ip6);
      clog << "(" << htons(sockAddr->addrIn6_.sin6_port) << ")";
      clog << endl;
   }
   idx++;
  }

  return 0;
}
