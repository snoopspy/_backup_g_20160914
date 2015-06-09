#include <iostream>
#include <string>
#include <thread>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <GTcpServer>

DEFINE_int32(family, AF_UNSPEC, "family");
DEFINE_string(localIp, "", "localIp");
DEFINE_int32(port, 10065, "port");

void acceptProc(GTcpServer* tcpServer) {
  GSockAddr acceptAddr;
  socklen_t addrLen;
  while (true) {
    DLOG(INFO) << "bef accept"; // gilgil temp
    GSock newSock = tcpServer->accept(&acceptAddr, &addrLen);
    DLOG(INFO) << "aft accept" << newSock; // gilgil temp
    if (newSock == -1) break;
    LOG(INFO) << "newSock=" << newSock;
  }
}

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  GTcpServer tcpServer;
  tcpServer.family_ = FLAGS_family;
  tcpServer.localIp_ = QString::fromStdString(FLAGS_localIp);
  tcpServer.port_ = (quint16)FLAGS_port;

  if (!tcpServer.open()) {
    LOG(ERROR) << tcpServer.err;
    return EXIT_FAILURE;
  }

  std::thread acceptThread(acceptProc, &tcpServer);

  std::cout << "Press enter to close\n";
  std::string s; std::getline(std::cin, s);
  DLOG(INFO) << "111"; // gilgil temp
  tcpServer.close();
  DLOG(INFO) << "222";
  acceptThread.join();
  DLOG(INFO) << "333";

  return 0;
}
