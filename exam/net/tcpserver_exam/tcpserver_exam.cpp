#include <gflags/gflags.h>
#include <glog/logging.h>
#include <iostream>
#include <mutex>
#include <set>
#include <thread>
#include <GParam>
#include <GTcpServer>

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

struct MyServer : GObj {
  Q_OBJECT
  Q_PROPERTY(GTcpServer* tcpServer READ getTcpServer)
  Q_PROPERTY(int bufSize MEMBER bufSize_)

public:

  bool open() override {
    if (!tcpServer_.open())
      return false;
    acceptThread_ = std::thread(&MyServer::acceptProc, this);
    return true;
  }

  bool close() override {
    tcpServer_.close();
    mutex_.lock();
    for (ConnThread* connThread: connThreads_)
      connThread->close();
    mutex_.unlock();
    return true;
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
    char buf[bufSize_];
    while (true) {
      ssize_t readLen = connThread->tcpSession_->read(buf, bufSize_ - 1);
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

  GTcpServer* getTcpServer() { return &tcpServer_; }
  GTcpServer tcpServer_;
  int bufSize_;
  std::thread acceptThread_;
  std::mutex mutex_;
  std::set<ConnThread*> connThreads_;
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
  GParam param(argc, argv);
  param.parse(&ms);

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

#include "tcpserver_exam.moc"
