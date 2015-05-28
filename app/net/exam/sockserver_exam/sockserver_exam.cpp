#include <iostream>
#include <GErr>
#include <GSock>

int backLog = 256;
constexpr size_t bufSize = 1024;
in_port_t port = 10065;

using namespace std;

void runTcpServer() {
  GSock acceptSock;
  if (!acceptSock.socket(AF_INET, SOCK_STREAM, 0)) { clog << lastErr << endl; return; }
  int optVal = 1;
  if (!acceptSock.setsockopt(SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal))) { clog << lastErr << endl; return; }
  GSockAddr acceptSockAddr(AF_INET, htons(port), INADDR_ANY);
  if (!acceptSock.bind(&acceptSockAddr, sizeof(struct sockaddr))) { clog << lastErr << endl; return; }
  if (!acceptSock.listen(backLog)) { clog << lastErr << endl; return; }

  while (true) {
    GSockAddr connSockAddr;
    socklen_t size = sizeof(struct sockaddr_in);
    GSock connSock = acceptSock.accept(&connSockAddr, &size);
    if (connSock == -1) break;

    while (true) {
      char buf[bufSize];
      ssize_t readLen = connSock.recv(buf, bufSize - 1, 0);
      if (readLen == 0 || readLen == -1) break;
      buf[readLen] = '\0';
      std::clog << buf << std::endl;
      ssize_t writeLen = connSock.send(buf, readLen, 0);
      if (writeLen == 0 || writeLen == -1) break;
    }
    connSock.close();
  }
}

int main() {
  runTcpServer();
}
