#include <iostream>
#include <gflags/gflags.h>
#include <GErr>
#include <GSock>

DEFINE_bool(ip6, false, "use ip6");
DEFINE_int32(localIp, INADDR_ANY, "local ip"); // in_addr_t
DEFINE_int32(port, 10065, "port"); // in_port_t
DEFINE_int32(backLog, 256, "bacl log"); // int
DEFINE_int64(bufSize, 1024, "buffer size"); // size_t

using namespace std;

void runTcpServer() {
  bool ip4 = !FLAGS_ip6;
  if (ip4) // gilgil temp 2015.06.03
    clog << "ip4\n";
  else
    clog << "ip6\n";

  sa_family_t family = ip4 ? AF_INET : AF_INET6;

  GSock acceptSock;

  if (!acceptSock.socket(family, SOCK_STREAM, 0)) { clog << lastErr << endl; return; }

  int optVal = 1;
  if (!acceptSock.setsockopt(SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal))) { clog << lastErr << endl; return; }

  GSockAddr acceptSockAddr;
  if (ip4)
    acceptSockAddr.init(AF_INET, htons((in_port_t)FLAGS_port), htonl((in_addr_t)FLAGS_localIp));
  else
    acceptSockAddr.init(AF_INET6, htons((in_port_t)FLAGS_port), 0, in6addr_any, 0);

  if (!acceptSock.bind(&acceptSockAddr)) { clog << lastErr << endl; return; }

  if (!acceptSock.listen(FLAGS_backLog)) { clog << lastErr << endl; return; }

  while (true) {
    GSockAddr connSockAddr;
    socklen_t size = sizeof(struct sockaddr_in);
    GSock connSock = acceptSock.accept(&connSockAddr, &size);
    if (connSock == -1) break;

    while (true) {
      char buf[FLAGS_bufSize];
      ssize_t readLen = connSock.recv(buf, FLAGS_bufSize - 1, 0);
      if (readLen == 0 || readLen == -1) break;
      buf[readLen] = '\0';
      std::clog << buf << std::endl;

      ssize_t writeLen = connSock.send(buf, readLen, 0);
      if (writeLen == 0 || writeLen == -1) break;
    }
    if (!connSock.close()) { clog << lastErr << endl; return; }
  }

  if (!acceptSock.close()) { clog << lastErr << endl; return; }
}

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  runTcpServer();
}
