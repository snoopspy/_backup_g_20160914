#include <gflags/gflags.h>
#include <iostream>
#include <thread>
#include <GAsyncTcpClient>
#include <GEventThread>

DEFINE_int32(family, AF_UNSPEC, "0:AF_UNSPEC 2:AF_INET 10:AF_INET6");
DEFINE_bool(nonBlock, true, "nonBlock");
DEFINE_string(localIp, "", "localIp");
DEFINE_string(localPort, "0", "localPort");
DEFINE_string(host, "localhost", "host");
DEFINE_string(port, "10065", "port");
DEFINE_int32(bufSize, 1024, "bufSize");

void readCallback(evutil_socket_t, short events, void* arg) {
  GAsyncTcpSession* tcpSession = (GAsyncTcpSession*)arg;
  char buf[FLAGS_bufSize];
  ssize_t readLen = tcpSession->read(buf, FLAGS_bufSize - 1);
  if (readLen == 0 || readLen == -1) {
    std::clog << "disconnected\n";
    GAsyncTcpClient* tcpClient = (GAsyncTcpClient*)tcpSession->parent();
    tcpClient->close();
    return;
  }
  buf[readLen] = '\0';
  std::clog << buf << std::endl;
}

void inputProc(GTcpClient* tcpClient, GEventThread* readThread) {
  while (true) {
    std::string s;
    std::getline(std::cin, s);
    if (s == "q") break;
    tcpClient->sock_.send(s.c_str(), s.length());
  }
  tcpClient->close();
  readThread->close(false);
}

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  GAsyncTcpClient tcpClient;
  tcpClient.family_ = FLAGS_family;
  tcpClient.nonBlock_ = FLAGS_nonBlock;
  tcpClient.localIp_ = QString::fromStdString(FLAGS_localIp);
  tcpClient.localPort_ = QString::fromStdString(FLAGS_localPort);
  tcpClient.host_ = QString::fromStdString(FLAGS_host);
  tcpClient.port_ = QString::fromStdString(FLAGS_port);

  if (!tcpClient.open()) {
    std::clog << tcpClient.err << std::endl;
    exit(EXIT_FAILURE);
  }

  GEventThread readThread;
  tcpClient.tcpSession_.assignEventBase(&readThread.eventBase_, readCallback);
  readThread.open();

  std::thread inputThread(inputProc, &tcpClient, &readThread);
  inputThread.detach();

  readThread.wait();
  tcpClient.close();

  return 0;
}
