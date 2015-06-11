#include <gflags/gflags.h>
#include <glog/logging.h>
#include <signal.h>
#include <thread>
#include <QThread>
#include <GEventSignal>
#include <GTcpServer>

DEFINE_int32(family, AF_UNSPEC, "family");
DEFINE_string(localIp, "", "localIp");
DEFINE_int32(port, 10065, "port");

void readProc(GTcpSession* tcpSession) {
  DLOG(INFO) << "connected";
  while (true) {
    char buf[1024];
    ssize_t readLen = tcpSession->read(buf, 1023);
    if (readLen == 0 || readLen == -1) break;
    buf[readLen] = '\0';
    LOG(INFO) << buf;
    tcpSession->write(buf, readLen);
  }
  DLOG(INFO) << "disconnected";
  delete tcpSession;
}

void acceptProc(GTcpServer* tcpServer) {
  while (true) {
    GSock newSock = tcpServer->accept();
    if (newSock == -1)
      break;
    GTcpSession* tcpSession = new GTcpSession(tcpServer, newSock);
    new std::thread(readProc, tcpSession);
  }
}

struct SignalThread : public QThread {
  SignalThread(GTcpServer* tcpServer) : tcpServer_(tcpServer) {}

  static void callback(evutil_socket_t, short, void* arg) {
    DLOG(INFO) << "beg callback";
    SignalThread* signalThread = (SignalThread*)arg;
    signalThread->tcpServer_->close();
    signalThread->eventSignal_.del();
    DLOG(INFO) << "end callback";
  }

  void run() override {
    eventSignal_.add();
    eventBase_.dispatch();
  }

  GTcpServer* tcpServer_;
  GEventBase eventBase_;
  GEventSignal eventSignal_{&eventBase_, SIGINT, callback, this};
};

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  GTcpServer tcpServer;
  tcpServer.family_ = FLAGS_family;
  tcpServer.localIp_ = QString::fromStdString(FLAGS_localIp);
  tcpServer.port_ = (quint16)FLAGS_port;

  if (!tcpServer.open()) {
    LOG(ERROR) << tcpServer.err;
    return EXIT_FAILURE;
  }

  std::thread acceptThread(acceptProc, &tcpServer);
  SignalThread signalThread{&tcpServer};
  signalThread.start();

  acceptThread.join();
  signalThread.wait();
}
