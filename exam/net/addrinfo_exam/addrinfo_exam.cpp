#include <arpa/inet.h> // for inet_ntop
#include <gflags/gflags.h>
#include <iostream>
#include <GAddrInfo>
#include <GIp>
#include <GStr>
#include <GSockAddr>

DEFINE_int32(family, AF_UNSPEC, "0:AF_UNSPEC(default) 2:AF_INET 10:AF_INET6");
DEFINE_int32(socktype, 0, "0:UNKNOWN(default) 1:SOCK_STREAM 2:SOCK_DGRAM");
DEFINE_int32(flags, 0, "flags");
DEFINE_string(host, "", "host");
DEFINE_string(port, "", "port");

using namespace std;

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  GAddrInfo addrInfo;
  addrInfo.hints_.ai_family = FLAGS_family;
  addrInfo.hints_.ai_socktype = FLAGS_socktype;
  addrInfo.hints_.ai_flags = FLAGS_flags;

  GErr* err = addrInfo.query(QString::fromStdString(FLAGS_host), QString::fromStdString(FLAGS_port));
  if (err != nullptr) {
    LOG(ERROR) << err;
    return EXIT_FAILURE;
  }

  int idx = 0;
  struct addrinfo* info;
  for (info = addrInfo.infos_; info != nullptr; info = info->ai_next) {
    clog << "idx=" << idx;

    clog  << " family=" << info->ai_family;
    switch (info->ai_family) {
      case AF_UNSPEC: clog << "(AF_UNSPEC)"; break;
      case AF_INET: clog << "(AF_INET)"; break;
      case AF_INET6: clog << "(AF_INET6)"; break;
    }

    clog << "\tsocktype=" << info->ai_socktype;
    switch (info->ai_socktype) {
      case SOCK_STREAM: clog << "(SOCK_STREAM)"; break;
      case SOCK_DGRAM: clog << "(SOCK_DGRAM)"; break;
      case SOCK_RAW: clog << "(SOCK_RAW)"; break;
    }

    clog << "\tprotocol=" << info->ai_protocol;
    switch (info->ai_protocol) {
      case IPPROTO_TCP: clog << "(IPPROTO_TCP)"; break;
      case IPPROTO_UDP: clog << "(IPPROTO_UDP)"; break;
      case IPPROTO_IP: clog << "(IPPROTO_IP)"; break;
    }

    clog << endl;

    if (info->ai_family == AF_INET) {
      struct sockaddr_in* addrIn = (struct sockaddr_in*)info->ai_addr;
      clog << "\tip=" << QString(GIp(ntohl(addrIn->sin_addr.s_addr)));
      clog << "\tport=" << htons(addrIn->sin_port);
      clog << endl;
    } else
   if (info->ai_family == AF_INET6) {
      struct sockaddr_in6* addrIn6 = (struct sockaddr_in6*)info->ai_addr;
      char str[INET6_ADDRSTRLEN];
      inet_ntop(info->ai_family, info->ai_addr, str, INET6_ADDRSTRLEN);
      clog << "\tip6=" << str;
      clog << "\tport=" << htons(addrIn6->sin6_port);
      clog << endl;
   }
   idx++;
  }

  return 0;
}
