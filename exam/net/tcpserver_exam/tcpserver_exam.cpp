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
#include <GTcpServer>

DEFINE_int32(family, AF_UNSPEC, "0:AF_UNSPEC 2:AF_INET 10:AF_INET6");
DEFINE_string(localIp, "", "localIp");
DEFINE_int32(port, 10065, "port");
DEFINE_bool(nonBlock, true, "nonBlock");
DEFINE_int32(bufSize, 1024, "bufSize");
DEFINE_int32(threadCnt, 4, "threadCnt");

GTcpServer tcpServer;
GEventThread acceptThread;
GEventThread* readThread;

struct SockMgr {
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
} _sockMgr;


void readCallback(evutil_socket_t fd, short, void* arg) {
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
  sock.send(buf, readLen);
}

void acceptCallback(evutil_socket_t, short, void*) {
  DLOG(INFO) << "beg acceptCallback";
  GSock newSock = tcpServer.accept();
  if (newSock == -1)
    return;
  if (!newSock.setNonblock()) {
    LOG(ERROR) << GLastErr();
  }
  _sockMgr.add(newSock);
  static int rr = 0;
  GEventSock* eventSock = new GEventSock(&readThread[rr].eventBase_, newSock, readCallback);
  eventSock->add();
  rr = (rr + 1) % FLAGS_threadCnt;
  DLOG(INFO) << "end acceptCallback";
}

void signalCallback(evutil_socket_t, short, void*) {
  DLOG(INFO) << "acceptCallback 111";
  acceptThread.close(false);
  for (int i = 0; i < FLAGS_threadCnt; i++) {
    readThread[i].close(false);
  }
  DLOG(INFO) << "acceptCallback 222";
}

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  tcpServer.family_ = FLAGS_family;
  tcpServer.localIp_ = QString::fromStdString(FLAGS_localIp);
  tcpServer.port_ = (quint16)FLAGS_port;
  tcpServer.nonBlock_ = FLAGS_nonBlock;
  DLOG(INFO) << "nonBlock=_" << tcpServer.nonBlock_;

  if (!tcpServer.open()) {
    LOG(ERROR) << tcpServer.err;
    return EXIT_FAILURE;
  }

  readThread = new GEventThread[FLAGS_threadCnt];

  GEventSock eventSock(&acceptThread.eventBase_, tcpServer.acceptSock_, acceptCallback);
  eventSock.add();

  GEventSignal eventSignal(&acceptThread.eventBase_, SIGINT, signalCallback, &acceptThread);
  eventSignal.add();

  acceptThread.open();
  for (int i = 0; i < FLAGS_threadCnt; i++)
    readThread[i].open();

  std::thread inputThread([](){
    while (true) {
      std::string s;
      std::getline(std::cin, s);
      //if (s == "q") break;
      _sockMgr.broadcast(s);
    }
  });
  inputThread.detach();

  acceptThread.wait();   DLOG(INFO) << "acceptThread.wait()";

  tcpServer.close();     DLOG(INFO) << "tcpServer.close()";
  _sockMgr.close();      DLOG(INFO) << "_sockMgr.close()";
  for (int i = 0; i < FLAGS_threadCnt; i++)
    readThread[i].wait();
  delete[] readThread;   DLOG(INFO) << "delete[] readThread";
  DLOG(INFO) << "application terminated";
  return 0;
}
