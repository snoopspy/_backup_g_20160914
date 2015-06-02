#include <cstring>
#include <iostream>
#include <GErr>
#include <GSock>

in_addr_t localIp = INADDR_ANY;
in_port_t localPort = 0;
in_addr_t ip = 0x7F000001;
in_port_t port = 10065;
size_t bufSize = 1024;
const char* msg = "hello world";

using namespace std;

void runTcpClient() {
  GSock sock;

  if (!sock.socket(AF_INET, SOCK_STREAM, 0)) { clog << lastErr << endl; return; }

  GSockAddr sockAddr(AF_INET, htons(localPort), htonl(localIp));
  if (!sock.bind(&sockAddr)) { clog << lastErr << endl; return; }

  sockAddr.init(AF_INET, htons(port), htonl(ip));
  if (!sock.connect(&sockAddr, sizeof(struct sockaddr_in))) { clog << lastErr << endl; return; }

  ssize_t writeLen = sock.send(msg, strlen(msg), 0);
  if (writeLen == 0 || writeLen == -1) return;

  char buf[bufSize];
  ssize_t readLen = sock.recv(buf, bufSize - 1, 0);
  if (readLen == 0 || readLen == -1) return;
  buf[readLen] = '\0';
  std::clog << buf << std::endl;

  if (!sock.close()) { clog << lastErr << endl; return; }
}

int main() {
  runTcpClient();
}
