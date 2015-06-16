#include <gflags/gflags.h>
#include <glog/logging.h>
#include <iostream>
#include <mutex>
#include <set>
#include <signal.h>
#include <thread>
#include <GEventSignal>
#include <GEventSock>
#include <GEventThread>
#include <GEventTimer>
#include <GTcpServer>

DEFINE_int32(family, AF_UNSPEC, "0:AF_UNSPEC 2:AF_INET 10:AF_INET6");
DEFINE_string(localIp, "", "localIp");
DEFINE_int32(port, 10065, "port");
DEFINE_bool(nonBlock, true, "nonBlock");
DEFINE_int32(bufSize, 1024, "bufSize");
DEFINE_int32(threadCnt, 4, "threadCnt");

struct ConnMgr {
  void clear() {
    socks_.clear();
  }

  void add(GSock sock) {
    mutex_.lock();
    socks_.insert(sock);
    mutex_.unlock();
  }

  void del(GSock sock) {
    mutex_.lock();
    socks_.erase(socks_.find(sock));
    mutex_.unlock();
  }

  void broadcast(std::string s) {
    mutex_.lock();
    for (GSock sock: socks_) {
      sock.send(s.c_str(), s.length());
    }
    mutex_.unlock();
  }

  void close() {
    mutex_.lock();
    for (GSock sock: socks_) {
      sock.shutdown();
      sock.close();
    }
    mutex_.unlock();
  }

  std::mutex mutex_;
  std::set<GSock> socks_;
};

struct MyServer {
  MyServer() {

  }

  virtual ~MyServer() {
    close();
  }

  bool open() {
    if (!tcpServer_.open()) {
      LOG(ERROR) << tcpServer_.err;
      return false;
    }
    connMgr_.clear();

    acceptEventSock_ = new GEventSock(
      &acceptThread_.eventBase_,
      tcpServer_.acceptSock_,
      acceptCallback,
      this);
    acceptEventSock_->add();

    acceptThread_.setObjectName("acceptThread_");
    acceptThread_.open();

    readThreads_ = new GEventThread[FLAGS_threadCnt];
    for (int i = 0; i < FLAGS_threadCnt; i++)
      readThreads_[i].open();

    return true;
  }

  bool close() {
    connMgr_.close();
    for (int i = 0; i < FLAGS_threadCnt; i++)
      readThreads_[i].close(false);
    tcpServer_.close();
    acceptThread_.close(false);
    delete acceptEventSock_;
    acceptEventSock_ = nullptr;
    for (int i = 0; i < FLAGS_threadCnt; i++)
      readThreads_[i].wait();
    acceptThread_.wait();

    delete[] readThreads_;
    return true;
  }

  static void acceptCallback(evutil_socket_t, short, void* arg) {
    DLOG(INFO) << "beg acceptCallback";
    MyServer* ms = (MyServer*)arg;
    GSock newSock = ms->tcpServer_.accept();
    if (newSock == -1)
      return;
    if (!newSock.setNonblock()) {
      LOG(ERROR) << GLastErr();
    }
    ms->connMgr_.add(newSock);
    static int rr = 0;
    GEventSock* eventSock = new GEventSock(&ms->readThreads_[rr].eventBase_, newSock, readCallback);
    eventSock->add();
    rr = (rr + 1) % FLAGS_threadCnt;
    DLOG(INFO) << "end acceptCallback";
  }

  static void readCallback(evutil_socket_t fd, short, void* arg) {
    GSock sock(fd);
    char buf[FLAGS_bufSize];
    ssize_t readLen = sock.recv(buf, FLAGS_bufSize - 1);
    if (readLen == 0 || readLen == -1) {
      sock.shutdown();
      sock.close();
      GEventSock* eventSock = (GEventSock*)arg;
      eventSock->del();
      delete eventSock;
      return;
    }
    buf[readLen] = '\0';
    DLOG(INFO) << buf;
    sock.send(buf, readLen);
  }

  GTcpServer tcpServer_;
  ConnMgr connMgr_;
  GEventThread acceptThread_;
  GEventSock* acceptEventSock_;
  GEventThread* readThreads_;
} ms;

void signalCallback(evutil_socket_t, short, void*) {
  ms.close();
}

int main(int argc, char* argv[]) {
  //QCoreApplication a(argc, argv);

  google::ParseCommandLineFlags(&argc, &argv, true);

  ms.tcpServer_.family_ = FLAGS_family;
  ms.tcpServer_.localIp_ = QString::fromStdString(FLAGS_localIp);
  ms.tcpServer_.port_ = (quint16)FLAGS_port;
  ms.tcpServer_.nonBlock_ = FLAGS_nonBlock;

  if (!ms.open()) {
    return EXIT_FAILURE;
  }

  //std::thread inputThread([](){
    while (true) {
      std::string s;
      std::getline(std::cin, s);
      if (s == "q") break;
      ms.connMgr_.broadcast(s);
    }
  //});
  //inputThread.detach();
  ms.close();
  DLOG(INFO) << "application terminated";
}
