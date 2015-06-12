#include <gflags/gflags.h>
#include <glog/logging.h>
#include <iostream>
#include <thread>
#include <GTcpServer>

DEFINE_int32(family, AF_UNSPEC, "0:AF_UNSPEC 2:AF_INET 10:AF_INET6");
DEFINE_string(localIp, "", "localIp");
DEFINE_int32(port, 10065, "port");
DEFINE_int32(bufSize, 1024, "bufSize");

void readProc(GTcpSession* tcpSession) {
  DLOG(INFO) << "connected";
  while (true) {
    char buf[FLAGS_bufSize];
    ssize_t readLen = tcpSession->read(buf, FLAGS_bufSize - 1);
    if (readLen == 0 || readLen == -1) break;
    buf[readLen] = '\0';
    LOG(INFO) << buf;
    tcpSession->write(buf, readLen);
  }
  DLOG(INFO) << "disconnected";
  delete tcpSession;
}

void acceptProc(GTcpServer* tcpServer) {
  while (true) {
    GTcpSession* newSession = tcpServer->accept();
    if (newSession == nullptr)
      break;
    new std::thread(readProc, newSession);
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

  while (true) {
    std::string s;
    std::getline(std::cin, s);
    if (s == "q") break;
    // broadcast() // gilgil temp 2015.06.13
  }
  tcpServer.close();

  acceptThread.join();
}
