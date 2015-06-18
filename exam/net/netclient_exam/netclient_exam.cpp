#include <gflags/gflags.h>
#include <iostream>
#include <thread>
#include <GNetClient>

DEFINE_int32(family, AF_UNSPEC, "0:AF_UNSPEC 2:AF_INET 10:AF_INET6");
DEFINE_bool(nonBlock, false, "nonBlock");
DEFINE_string(localIp, "", "localIp");
DEFINE_string(localPort, "0", "localPort");
DEFINE_string(host, "localhost", "host");
DEFINE_string(port, "10065", "port");
DEFINE_int32(bufSize, 1024, "bufSize");

struct MyClient {
  GNetClient netClient_;
  GSock sock_;
  std::thread readThread_;

  bool open() {
    sock_ = netClient_.createSock();
    if (sock_ == INVALID_SOCKET)
      return false;
    readThread_ = std::thread(&MyClient::readProc, this);
    return true;
  }

  void close() {
    sock_.shutdown();
    sock_.close();
  }

  void wait() {
    readThread_.join();
  }

  void readProc() {
    std::clog << "connected\n";
    char buf[FLAGS_bufSize];
    while (true) {
      ssize_t readLen = sock_.recv(buf, FLAGS_bufSize - 1);
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
    mc.sock_.send(s.c_str(), s.length());
  }
  mc.close();
}

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  mc.netClient_.family_ = FLAGS_family;
  mc.netClient_.nonBlock_ = FLAGS_nonBlock;
  mc.netClient_.localIp_ = QString::fromStdString(FLAGS_localIp);
  mc.netClient_.localPort_ = QString::fromStdString(FLAGS_localPort);
  mc.netClient_.host_ = QString::fromStdString(FLAGS_host);
  mc.netClient_.port_ = QString::fromStdString(FLAGS_port);

  if (!mc.open()) {
    std::clog << mc.netClient_.err << std::endl;
    exit(EXIT_FAILURE);
  }

  std::thread inputThread(inputProc);
  inputThread.detach();

  mc.wait();
  mc.close();

  return 0;
}
