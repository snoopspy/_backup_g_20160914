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
DEFINE_int32(backLog, 1024, "backLog");
DEFINE_int32(bufSize, 1024, "bufSize");

struct ConnThread {
  ConnThread(GTcpSession* tcpSession) : tcpSession_(tcpSession) {}
  ~ConnThread() {
    delete tcpSession_;
  }

  void close() {
    tcpSession_->close();
  }

  void wait() {
    thread_.join();
  }

  GTcpSession* tcpSession_;
  std::thread thread_;
};

struct MyServer {
  GTcpServer tcpServer_;
  std::thread acceptThread_;
  std::mutex mutex_;
  std::set<ConnThread*> connThreads_;

  bool open() {
    if (!tcpServer_.open())
      return false;
    acceptThread_ = std::thread(&MyServer::acceptProc, this);
    return true;
  }

  void close() {
    tcpServer_.close();
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
      GTcpSession* newSession = tcpServer_.accept();
      if (newSession == nullptr) break;
      ConnThread* connThread = new ConnThread(newSession);
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
      ssize_t readLen = connThread->tcpSession_->read(buf, FLAGS_bufSize - 1);
      if (readLen == 0 || readLen == -1) break;
      buf[readLen] = '\0';
      std::clog << buf << std::endl;
      connThread->tcpSession_->write(buf, readLen);
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
      connThread->tcpSession_->write(s.c_str(), s.length());
    ms.mutex_.unlock();
  }
  ms.close();
}

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  ms.tcpServer_.family_ = FLAGS_family;
  ms.tcpServer_.nonBlock_ = FLAGS_nonBlock;
  ms.tcpServer_.localIp_ = QString::fromStdString(FLAGS_localIp);
  ms.tcpServer_.port_ = QString::fromStdString(FLAGS_port);

  if (!ms.open()) {
    std::clog << ms.tcpServer_.err << std::endl;
    exit(EXIT_FAILURE);
  }

  std::thread inputThread(inputProc);
  inputThread.detach();

  ms.wait();
  ms.close();

  return 0;
}
