#include <signal.h>
#include <thread>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <GTcpServer>
#include <GEventSignal>

DEFINE_int32(family, AF_UNSPEC, "family");
DEFINE_string(localIp, "", "localIp");
DEFINE_int32(port, 10065, "port");

void readProc(GTcpSession* tcpSession) {
  DLOG(INFO) << "readProc " << tcpSession->sock_;
  tcpSession->close();
}

void acceptProc(GTcpServer* tcpServer) {
  GSockAddr acceptAddr;
  while (true) {
    socklen_t addrLen = sizeof(GSockAddr);
    GSock newSock = tcpServer->accept(&acceptAddr, &addrLen);
    if (newSock == -1) {
      break;
    }
    GTcpSession* tcpSession = new GTcpSession(tcpServer, newSock);
    new std::thread(readProc, tcpSession);
  }
}

struct SignalMgr {
  SignalMgr(GTcpServer* tcpServer) : tcpServer_(tcpServer) {}

  static void callback(evutil_socket_t, short, void* arg) {
    DLOG(INFO) << "beg callback";
    SignalMgr* signalMgr = (SignalMgr*)arg;
    signalMgr->tcpServer_->acceptClose();
    signalMgr->eventSignal_.del();
  }

  static void run(SignalMgr* signalMgr) {
    signalMgr->eventSignal_.add();
    signalMgr->eventBase_.dispatch();
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
  SignalMgr signalMgr{&tcpServer};
  std::thread signalThread(SignalMgr::run, &signalMgr);

  acceptThread.join();
  signalThread.join();
}
