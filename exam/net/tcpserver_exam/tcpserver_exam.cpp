#include <gflags/gflags.h>
#include <glog/logging.h>
#include <signal.h>
#include <thread>
#include <GEventSignal>
#include <GEventThread>
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
    GTcpSession* newSession = tcpServer->accept();
    if (newSession == nullptr)
      break;
    new std::thread(readProc, newSession);
  }
}

void signalCallback(evutil_socket_t, short, void* arg) {
  DLOG(INFO) << "beg callback";
  GTcpServer* tcpServer = (GTcpServer*)arg;
  tcpServer->close();
  DLOG(INFO) << "end callback";
}

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

  GEventThread eventThread;
  GEventSignal eventSignal{&eventThread.eventBase_, SIGINT, signalCallback, &tcpServer, EV_SIGNAL};
  eventSignal.add();
  eventThread.start();
  std::thread acceptThread(acceptProc, &tcpServer);

  acceptThread.join();
  eventThread.wait();
}
