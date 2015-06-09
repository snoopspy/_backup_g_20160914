#include <iostream>
#include <string>
#include <thread>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <GTcpServer>
#include <QThread>

DEFINE_int32(family, AF_UNSPEC, "family");
DEFINE_string(localIp, "", "localIp");
DEFINE_int32(port, 10065, "port");

void readProc(GTcpSession* tcpSession) {
  DLOG(INFO) << "readProc " << tcpSession->sock_;
  tcpSession->close();
}

struct AcceptProc : QThread {
  AcceptProc(GTcpServer* tcpServer) : tcpServer_(tcpServer) {}
  GTcpServer* tcpServer_;
protected:
  void run() override {
    GSockAddr acceptAddr;
    socklen_t addrLen = sizeof(GSockAddr);
    while (true) {
      DLOG(INFO) << "bef accept"; // gilgil temp
      GSock newSock = tcpServer_->accept(&acceptAddr, &addrLen);
      DLOG(INFO) << "aft accept " << newSock; // gilgil temp
      LOG(INFO) << "newSock=" << newSock;
      if (newSock == -1) break;
      GTcpSession* tcpSession = new GTcpSession(tcpServer_, newSock);
      new std::thread(readProc, tcpSession);
    }
  }
};

void acceptProc(GTcpServer* tcpServer) {
  GSockAddr acceptAddr;
  socklen_t addrLen = sizeof(GSockAddr);
  while (true) {
    DLOG(INFO) << "bef accept"; // gilgil temp
    GSock newSock = tcpServer->accept(&acceptAddr, &addrLen);
    DLOG(INFO) << "aft accept " << newSock; // gilgil temp
    LOG(INFO) << "newSock=" << newSock;
    if (newSock == -1) break;
    GTcpSession* tcpSession = new GTcpSession(tcpServer, newSock);
    new std::thread(readProc, tcpSession);
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
  DLOG(INFO) << "tcpServer sock=" << tcpServer.acceptSock_;

  //std::thread acceptThread(acceptProc, &tcpServer);
  AcceptProc* acceptProc = new AcceptProc(&tcpServer);
  acceptProc->start();

  //std::cout << "Press enter to close\n";
  //std::string s; std::getline(std::cin, s);
  std::this_thread::sleep_for(std::chrono::seconds(2));
  DLOG(INFO) << "111"; // gilgil temp

  int sd = tcpServer.acceptSock_;
  ::shutdown(sd, 3);
  ::close(sd);

  DLOG(INFO) << "222";
  tcpServer.close();
  DLOG(INFO) << "333";
  //acceptThread.join();
  acceptProc->wait();
  DLOG(INFO) << "444";

  return 0;
}
