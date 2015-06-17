#include <gflags/gflags.h>
#include <glog/logging.h>
#include <iostream>
#include <mutex>
#include <set>
#include <thread>
#include <GTcpServer>

DEFINE_int32(family, AF_UNSPEC, "0:AF_UNSPEC 2:AF_INET 10:AF_INET6");
DEFINE_bool(nonBlock, false, "nonBlock");
DEFINE_string(localIp, "", "localIp");
DEFINE_string(port, "10065", "port");
DEFINE_int32(bufSize, 1024, "bufSize");

std::mutex _mutex;
std::set<GSock> _socks;

void readProc(GSock sock) {
  char buf[FLAGS_bufSize];
  while (true) {
    ssize_t readLen = sock.recv(buf, FLAGS_bufSize - 1);
    if (readLen == 0 || readLen == -1) break;
    buf[readLen] = '\0';
    std::clog << buf << std::endl;
  }
  _mutex.lock();
  _socks.erase(sock);
  _mutex.unlock();
}

void acceptProc(GSock acceptSock) {
  while (true) {
    GSock newSock = acceptSock.accept();
    if (newSock == -1) break;
    _mutex.lock();
    _socks.insert(newSock);
    _mutex.unlock();
    std::thread readThread(readProc, newSock);
    readThread.detach();
  }
}

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  GTcpServer tcpServer;
  tcpServer.family_ = FLAGS_family;
  tcpServer.nonBlock_ = FLAGS_nonBlock;
  tcpServer.localIp_ = QString::fromStdString(FLAGS_localIp);
  tcpServer.port_ = QString::fromStdString(FLAGS_port);

  if (!tcpServer.open()) {
    std::clog << tcpServer.err << std::endl;
    exit(EXIT_FAILURE);
  }

  std::thread acceptThread(acceptProc, tcpServer.acceptSock_);

  while (true) {
    std::string s;
    std::getline(std::cin, s);
    if (s == "q") break;
    _mutex.lock();
    for (GSock sock: _socks)
      sock.send(s.c_str(), s.length());
    _mutex.unlock();
  }

  tcpServer.close();
  acceptThread.join();

  return 0;
}
