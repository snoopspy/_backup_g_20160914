#include <gflags/gflags.h>
#include <iostream>
#include <thread>
#include <GTcpClient>

DEFINE_int32(family, AF_UNSPEC, "0:AF_UNSPEC 2:AF_INET 10:AF_INET6");
DEFINE_bool(nonBlock, false, "nonBlock");
DEFINE_string(localIp, "", "localIp");
DEFINE_string(localPort, "0", "localPort");
DEFINE_string(host, "localhost", "host");
DEFINE_string(port, "10065", "port");
DEFINE_int32(bufSize, 1024, "bufSize");

void readProc(GTcpClient* tcpClient) {
  std::clog << "connected\n";
  char buf[FLAGS_bufSize];
  while (true) {
    ssize_t readLen = tcpClient->sock_.recv(buf, FLAGS_bufSize - 1);
    if (readLen == 0 || readLen == -1) break;
    buf[readLen] = '\0';
    std::clog << buf << std::endl;
  }
  std::clog << "disconnected\n";
}

void inputProc(GTcpClient* tcpClient) {
  while (true) {
    std::string s;
    std::getline(std::cin, s);
    if (s == "q") break;
    tcpClient->sock_.send(s.c_str(), s.length());
  }
  tcpClient->close();
}

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  GTcpClient tcpClient;
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

  std::thread readThread(readProc, &tcpClient);
  std::thread inputThread(inputProc, &tcpClient);
  inputThread.detach();

  readThread.join();
  tcpClient.close();

  return 0;
}
