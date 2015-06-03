#include <gflags/gflags.h>
#include <glog/logging.h>
#include <GErr>
#include <GSock>

DEFINE_bool(ip6, false, "use ip6");
DEFINE_bool(ip6only, false, "use ip6 only");
DEFINE_int32(localIp, INADDR_ANY, "local ip"); // in_addr_t
DEFINE_int32(port, 10065, "port"); // in_port_t
DEFINE_int32(backLog, 256, "bacl log"); // int
DEFINE_int64(bufSize, 1024, "buffer size"); // size_t

using namespace std;

void runTcpServer() {
  bool ip4 = !FLAGS_ip6;

  GSock acceptSock;
  if (ip4) {
    if (!acceptSock.socket(AF_INET, SOCK_STREAM, 0)) { LOG(ERROR) << lastErr; return; }
  } else {
    if (!acceptSock.socket(AF_INET6, SOCK_STREAM, 0)) { LOG(ERROR) << lastErr; return; }
  }

  if (!acceptSock.setsockopt(SOL_SOCKET, SO_REUSEADDR)) { LOG(ERROR) << lastErr; return; }

  GSockAddr bindAddr;
  if (ip4) {
    bindAddr.init(AF_INET, htons(FLAGS_port), htonl(FLAGS_localIp));
  } else {
    if (FLAGS_ip6only) {
      if (!acceptSock.setsockopt(IPPROTO_IPV6, IPV6_V6ONLY)) { LOG(ERROR) << lastErr; return; }
    }
    bindAddr.init(AF_INET6, htons(FLAGS_port), 0, in6addr_any, 0);
  }
  if (!acceptSock.bind(&bindAddr)) { LOG(ERROR) << lastErr; return; }

  if (!acceptSock.listen(FLAGS_backLog)) { LOG(ERROR) << lastErr; return; }

  while (true) {
    GSockAddr connSockAddr;
    socklen_t size = sizeof(struct sockaddr_in);
    GSock connSock = acceptSock.accept(&connSockAddr, &size);
    if (connSock == -1) break;

    while (true) {
      char buf[FLAGS_bufSize];
      ssize_t readLen = connSock.recv(buf, FLAGS_bufSize - 1);
      if (readLen == 0 || readLen == -1) break;
      buf[readLen] = '\0';
      LOG(INFO) << buf;

      ssize_t writeLen = connSock.send(buf, readLen);
      if (writeLen == 0 || writeLen == -1) break;
    }
    if (!connSock.close()) { LOG(ERROR) << lastErr; return; }
  }

  if (!acceptSock.close()) { LOG(ERROR) << lastErr; return; }
}

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  runTcpServer();
}
