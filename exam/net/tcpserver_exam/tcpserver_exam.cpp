#include <QCoreApplication>
#include <signal.h>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <iostream>
#include <mutex>
#include <set>
#include <thread>
#include <GEventSignal>
#include <GEventSock>
#include <GEventThread>
#include <GTcpServer>

DEFINE_int32(family, AF_UNSPEC, "0:AF_UNSPEC 2:AF_INET 10:AF_INET6");
DEFINE_string(localIp, "", "localIp");
DEFINE_int32(port, 10065, "port");
DEFINE_bool(nonBlock, false, "nonBlock");
DEFINE_int32(bufSize, 1024, "bufSize");

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


void readProc(GSock sock) {
  DLOG(INFO) << "connected";
  while (true) {
    char buf[FLAGS_bufSize];
    ssize_t readLen = sock.recv(buf, FLAGS_bufSize - 1);
    if (readLen == 0 || readLen == -1) break;
    buf[readLen] = '\0';
    LOG(INFO) << buf;
    sock.send(buf, readLen);
  }
  DLOG(INFO) << "disconnected";
  _sockMgr.del(sock);
  sock.shutdown();
  sock.close();
}

void acceptProc(GTcpServer* tcpServer) {
  DLOG(INFO) << "beg acceptProc";
  while (true) {
    GSock newSock = tcpServer->accept();
    if (newSock == -1)
      break;
    _sockMgr.add(newSock);
    std::thread readThread(readProc, newSock);
    readThread.detach();
  }
  DLOG(INFO) << "end acceptProc";
}

void acceptCallback(evutil_socket_t, short, void* arg) {
  DLOG(INFO) << "beg acceptCallback";
  GTcpServer* tcpServer = (GTcpServer*)arg;
  GSock newSock = tcpServer->accept();
  if (newSock == -1)
    return;
  _sockMgr.add(newSock);
  std::thread readThread(readProc, newSock);
  readThread.detach();
  DLOG(INFO) << "end acceptCallback";
}

void signalCallback(evutil_socket_t, short, void* arg) {
  DLOG(INFO) << "stt acceptCallback";
  GEventBase* eventBase = (GEventBase*)arg;
  eventBase->loopbreak();
  DLOG(INFO) << "end acceptCallback";
}

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  GTcpServer tcpServer;
  tcpServer.family_ = FLAGS_family;
  tcpServer.localIp_ = QString::fromStdString(FLAGS_localIp);
  tcpServer.port_ = (quint16)FLAGS_port;
  tcpServer.nonBlock_ = FLAGS_nonBlock;
  DLOG(INFO) << "nonBlock=_" << tcpServer.nonBlock_;

  if (!tcpServer.open()) {
    LOG(ERROR) << tcpServer.err;
    return EXIT_FAILURE;
  }

  GEventThread acceptThread;
  GEventSock eventSock(&acceptThread.eventBase_, tcpServer.acceptSock_, acceptCallback, &tcpServer);
  eventSock.add();

  GEventSignal eventSignal(&acceptThread.eventBase_, SIGINT, signalCallback, &acceptThread.eventBase_);
  eventSignal.add();
  acceptThread.start();

  std::thread inputThread([](){
    while (true) {
      std::string s;
      std::getline(std::cin, s);
      //if (s == "q") break;
      _sockMgr.broadcast(s);
    }
  });
  inputThread.detach();

  acceptThread.wait();
  tcpServer.close();
  _sockMgr.close();
  DLOG(INFO) << "application terminated";
  return 0;
}
