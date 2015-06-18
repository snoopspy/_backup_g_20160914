#include <gflags/gflags.h>
#include <glog/logging.h>
#include <iostream>
#include <mutex>
#include <set>
#include <thread>
#include <GNetServer>

DEFINE_int32(family, AF_UNSPEC, "0:AF_UNSPEC 2:AF_INET 10:AF_INET6");
DEFINE_bool(nonBlock, false, "nonBlock");
DEFINE_string(localIp, "", "localIp");
DEFINE_string(port, "10065", "port");
DEFINE_int32(backLog, 1024, "backLog");
DEFINE_int32(bufSize, 1024, "bufSize");

struct ConnThread {
  void close() {
    sock_.shutdown();
    sock_.close();
  }

  void wait() {
    thread_.join();
  }

  GSock sock_;
  std::thread thread_;
};

struct MyServer {
  GNetServer netServer_;
  GSock acceptSock_;
  std::thread acceptThread_;
  std::mutex mutex_;
  std::set<ConnThread*> connThreads_;

  bool open() {
    if (!netServer_.checkLocalIpAndPort())
      return false;
    acceptSock_ = netServer_.bind();
    if (acceptSock_ == INVALID_SOCKET)
      return false;
    if (!acceptSock_.listen(FLAGS_backLog))
      return false;
    acceptThread_ = std::thread(&MyServer::acceptProc, this);
    return true;
  }

  void close() {
    acceptSock_.shutdown();
    acceptSock_.close();
    mutex_.lock();
    for (ConnThread* connThread: connThreads_)
      connThread->close();
    mutex_.unlock();
  }

  void wait() {
    acceptThread_.join();
    mutex_.lock();
    for (ConnThread* connThread: connThreads_)
      connThread->wait();
    mutex_.unlock();
  }

  void acceptProc() {
    while (true) {
      GSock newSock = acceptSock_.accept();
      if (newSock == INVALID_SOCKET) break;
      ConnThread* connThread = new ConnThread;
      connThread->sock_ = newSock;
      connThread->thread_ = std::thread(&MyServer::readProc, this, connThread);
      mutex_.lock();
      connThreads_.insert(connThread);
      mutex_.unlock();
    }
  }

  void readProc(ConnThread* connThread) {
    std::clog << "connected\n";
    char buf[FLAGS_bufSize];
    while (true) {
      ssize_t readLen = connThread->sock_.recv(buf, FLAGS_bufSize - 1);
      if (readLen == 0 || readLen == -1) break;
      buf[readLen] = '\0';
      std::clog << buf << std::endl;
      connThread->sock_.send(buf, readLen);
    }
    mutex_.lock();
    connThreads_.erase(connThread);
    mutex_.unlock();
    std::clog << "disconnected\n";
  }
} ms;

void inputProc() {
  while (true) {
    std::string s;
    std::getline(std::cin, s);
    if (s == "q") break;
    ms.mutex_.lock();
    for (ConnThread* connThread: ms.connThreads_)
      connThread->sock_.send(s.c_str(), s.length());
    ms.mutex_.unlock();
  }
  ms.close();
}

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  ms.netServer_.family_ = FLAGS_family;
  ms.netServer_.nonBlock_ = FLAGS_nonBlock;
  ms.netServer_.localIp_ = QString::fromStdString(FLAGS_localIp);
  ms.netServer_.port_ = QString::fromStdString(FLAGS_port);

  if (!ms.open()) {
    std::clog << ms.netServer_.err << std::endl;
    exit(EXIT_FAILURE);
  }

  std::thread inputThread(inputProc);
  inputThread.detach();

  ms.wait();
  ms.close();

  return 0;
}
