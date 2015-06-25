#include <iostream>
#include <GAddrInfo>
#include <GIp>
#include <GIp6>
#include <GParam>
#include <GStr>
#include <GSockAddr>

struct Option : GObj {
  Q_OBJECT
  Q_PROPERTY(int flags MEMBER flags_)
  Q_PROPERTY(int family MEMBER family_)
  Q_PROPERTY(int socktype MEMBER socktype_)
  Q_PROPERTY(QString host MEMBER host_)
  Q_PROPERTY(QString port MEMBER port_)

public:
  int flags_{0}; // 1:AI_PASSIVE
  int family_{AF_UNSPEC}; // 0:AF_UNSPEC 2:AF_INET 10:AF_INET6
  int socktype_{0}; // 0:UNKNOWN 1:SOCK_STREAM 2:SOCK_DGRAM
  QString host_{""};
  QString port_{"0"};
} option;

using namespace std;

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  { GParam param(argc, argv);
    param.parse(&option);
  }

  GAddrInfo addrInfo;
  struct addrinfo hints;

  memset(&hints, 0, sizeof(hints));
  hints.ai_flags = option.flags_;
  hints.ai_family = option.family_;
  hints.ai_socktype = option.socktype_;

  GErr* err = addrInfo.query(hints, qPrintable(option.host_), qPrintable(option.port_));
  if (err != nullptr) {
    clog << err << endl;
    delete err;
    return EXIT_FAILURE;
  }

  clog << "idx\taddrlen\tfamily\t\tsocktype\tprotocol\tip(port)\n";
  int idx = 0;
  struct addrinfo* info;
  for (info = addrInfo.info_; info != nullptr; info = info->ai_next) {
    clog << idx;

    clog << "\t" << info->ai_addrlen;

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
    if (sockAddr->family() == AF_INET)
      clog << "\t" << QString(sockAddr->ip());
    else
      clog << "\t" << QString(sockAddr->ip6());
    clog << "(" << sockAddr->port() << ")";

    clog << endl;
    idx++;
  }

  return 0;
}

#include "addrinfo_exam.moc"
