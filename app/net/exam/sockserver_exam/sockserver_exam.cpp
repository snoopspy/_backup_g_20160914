#include <iostream>
#include <GErr>
#include <GSock>

in_port_t port = 10065;
int backLog = 256;

void runTcpServer() {
  GSock acceptSock;
  GSockAddr acceptSockAddr;

  acceptSock.socket(AF_INET, SOCK_STREAM, 0);
  acceptSockAddr.init(AF_INET, htons(port), INADDR_ANY);
  acceptSock.bind(&acceptSockAddr, sizeof(struct sockaddr));
  acceptSock.listen(backLog);

  while (true) {
    GSockAddr newSockAddr;
    socklen_t size = sizeof(struct sockaddr_in);
    GSock newSock = acceptSock.accept(&newSockAddr, &size);
    if (newSock == -1) break;


  }



}

int main(int argc, char* argv[]) {
  runTcpServer();

}
