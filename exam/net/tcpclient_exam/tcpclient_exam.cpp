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

struct MyClient {
  GTcpClient tcpClient_;
  std::thread readThread_;

  bool open() {
    if (!tcpClient_.open())
      return false;
    readThread_ = std::thread(&MyClient::readProc, this);
    return true;
  }

  void close() {
    tcpClient_.close();
  }

  void wait() {
    readThread_.join();
  }

  void readProc() {
    std::clog << "connected\n";
    char buf[FLAGS_bufSize];
    while (true) {
      ssize_t readLen = tcpClient_.tcpSession_->read(buf, FLAGS_bufSize - 1);
      if (readLen == 0 || readLen == -1) break;
      buf[readLen] = '\0';
      std::clog << buf << std::endl;
    }
    std::clog << "disconnected\n";
  }
} mc;

void inputProc() {
  while (true) {
    std::string s;
    std::getline(std::cin, s);
    if (s == "q") break;
    mc.tcpClient_.tcpSession_->write(s.c_str(), s.length());
  }
  mc.close();
}

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  mc.tcpClient_.family_ = FLAGS_family;
  mc.tcpClient_.nonBlock_ = FLAGS_nonBlock;
  mc.tcpClient_.localIp_ = QString::fromStdString(FLAGS_localIp);
  mc.tcpClient_.localPort_ = QString::fromStdString(FLAGS_localPort);
  mc.tcpClient_.host_ = QString::fromStdString(FLAGS_host);
  mc.tcpClient_.port_ = QString::fromStdString(FLAGS_port);

  if (!mc.open()) {
    std::clog << mc.tcpClient_.err << std::endl;
    exit(EXIT_FAILURE);
  }

  std::thread inputThread(inputProc);
  inputThread.detach();

  mc.wait();
  mc.close();

  return 0;
}
