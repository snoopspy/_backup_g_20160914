#include <gflags/gflags.h>
#include <glog/logging.h>
#include <iostream>
#include <GTcpClient>
#include <GEventSock>
#include <GEventThread>

DEFINE_int32(family, AF_UNSPEC, "0:AF_UNSPEC 2:AF_INET 10:AF_INET6");
DEFINE_string(localIp, "", "localIp");
DEFINE_int32(localPort, 0, "locapPort");
DEFINE_string(host, "localhost", "host");
DEFINE_int32(port, 10065, "port");
DEFINE_bool(nonBlock, true, "nonBlock");
DEFINE_int32(bufSize, 1024, "bufSize");
DEFINE_int32(threadCnt, 4, "threadCnt");

struct MyClient {
  bool open() {
    if (!tcpClient_.open()) {
      LOG(ERROR) << tcpClient_.err;
      return false;
    }

    eventSock_ = new GEventSock(
      &readThread_.eventBase_,
      tcpClient_.sock_,
      readCallback);
    eventSock_->add();

    readThread_.setObjectName("readThread_");
    readThread_.open();

    return true;
  }

  bool close() {
    tcpClient_.close();
    readThread_.close();
    delete eventSock_;
    return true;
  }

  static void readCallback(evutil_socket_t fd, short, void*) {
    GSock sock(fd);
    char buf[FLAGS_bufSize];
    ssize_t readLen = sock.recv(buf, FLAGS_bufSize - 1);
    if (readLen == 0 || readLen == -1) {
      DLOG(INFO) << "disconnected";
      sock.shutdown();
      sock.close();
      return;
    }
    buf[readLen] = '\0';
    DLOG(INFO) << buf;
  }

  GTcpClient tcpClient_;
  GEventThread readThread_;
  GEventSock* eventSock_;
} mc;

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  mc.tcpClient_.family_ = FLAGS_family;
  mc.tcpClient_.localIp_ = QString::fromStdString(FLAGS_localIp);
  mc.tcpClient_.localPort_ = (quint16)(FLAGS_localPort);
  mc.tcpClient_.host_ = QString::fromStdString(FLAGS_host);
  mc.tcpClient_.port_ = (quint16)FLAGS_port;
  mc.tcpClient_.nonBlock_ = FLAGS_nonBlock;

  if (!mc.open()) {
    return EXIT_FAILURE;
  }

  while (true) {
    std::string s;
    std::getline(std::cin, s);
    if (s == "q") break;
    mc.tcpClient_.sock_.send(s.c_str(), s.length());
  }

  mc.close();
  DLOG(INFO) << "application terminated";
  return 0;
}
