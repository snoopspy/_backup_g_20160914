#include <cstring>
#include <iostream>
#include <gflags/gflags.h>
#include <GErr>
#include <GSock>

DEFINE_bool(ip6, false, "use ip6");
DEFINE_int32(localIp, INADDR_ANY, "local ip"); // in_addr_t
DEFINE_int32(localPort, 0, "local port"); // in_port_t
DEFINE_int32(ip, 0x7F000001, "ip"); // in_addr_t
DEFINE_int32(port, 10065, "port"); // in_port_t
DEFINE_int64(bufSize, 1024, "buffer size"); // size_t
DEFINE_string(msg, "hello world", "message");

using namespace std;

void runTcpClient() {
  if (FLAGS_ip6) // gilgil temp 2015.06.03
    clog << "ip6\n";
  else
    clog << "ip4\n";

  GSock sock;

  if (!sock.socket(AF_INET, SOCK_STREAM, 0)) { clog << lastErr << endl; return; }

  GSockAddr sockAddr(AF_INET, htons((in_port_t)FLAGS_localPort), htonl((in_addr_t)FLAGS_localIp));
  if (!sock.bind(&sockAddr)) { clog << lastErr << endl; return; }

  sockAddr.init(AF_INET, htons((in_port_t)FLAGS_port), htonl((in_addr_t)FLAGS_ip));
  if (!sock.connect(&sockAddr)) { clog << lastErr << endl; return; }

  ssize_t writeLen = sock.send(FLAGS_msg.c_str(), FLAGS_msg.length(), 0);
  if (writeLen == 0 || writeLen == -1) return;

  char buf[FLAGS_bufSize];
  ssize_t readLen = sock.recv(buf, FLAGS_bufSize - 1, 0);
  if (readLen == 0 || readLen == -1) return;
  buf[readLen] = '\0';
  std::clog << buf << std::endl;

  if (!sock.close()) { clog << lastErr << endl; return; }
}

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  runTcpClient();
}
