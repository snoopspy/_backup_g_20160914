#include <cstring>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <GErr>
#include <GSock>

DEFINE_bool(ip6, false, "use ip6");
DEFINE_int32(localIp, INADDR_ANY, "local ip"); // in_addr_t
DEFINE_int32(localPort, 0, "local port"); // in_port_t
DEFINE_int32(ip, 0x7F000001, "ip"); // in_addr_t
DEFINE_int32(port, 10065, "port"); // in_port_t
DEFINE_int64(bufSize, 1024, "buffer size"); // size_t
DEFINE_string(msg, "hello world", "message");

void runTcpClient() {
  bool ip4 = !FLAGS_ip6;

  GSock sock;
  if (ip4) {
    if (!sock.socket(AF_INET, SOCK_STREAM, 0)) { LOG(ERROR) << GLastErr(); return; }
  } else {
    if (!sock.socket(AF_INET6, SOCK_STREAM, 0)) { LOG(ERROR) << GLastErr(); return; }
  }

  GSockAddr bindAddr;
  if (ip4) {
    bindAddr.init(AF_INET, htons(FLAGS_localPort), htonl(FLAGS_localIp));
  } else {
    bindAddr.init(AF_INET6, htons(FLAGS_localPort), 0, in6addr_any, 0);
  }
  if (!sock.bind(&bindAddr)) { LOG(ERROR) << GLastErr(); return; }

  GSockAddr connAddr;
  if (ip4) {
    connAddr.init(AF_INET, htons(FLAGS_port), htonl(FLAGS_ip));
  } else {
    connAddr.init(AF_INET6, htons(FLAGS_port), 0, in6addr_loopback, 0);
  }
  if (!sock.connect(&connAddr)) LOG(ERROR) << GLastErr();

  ssize_t writeLen = sock.send(FLAGS_msg.c_str(), FLAGS_msg.length());
  if (writeLen == 0 || writeLen == -1) return;

  char buf[FLAGS_bufSize];
  ssize_t readLen = sock.recv(buf, FLAGS_bufSize - 1);
  if (readLen == 0 || readLen == -1) return;
  buf[readLen] = '\0';
  LOG(INFO) << buf;

  if (!sock.close()) { LOG(ERROR) << GLastErr(); return; }
}

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  runTcpClient();
}
