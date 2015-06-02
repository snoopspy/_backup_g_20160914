#include <glog/logging.h>
#include <GErr>
#include <GEventSock>
#include <GSock>

void callback(evutil_socket_t fd, short events, void* arg) {
  DLOG(INFO) << "fd=" << fd << " event=" << events;

  GSock sock(fd);
  char buf[1024];
  ssize_t readLen = sock.recv(buf, 1023, 0);
  if (readLen == 0 || readLen == -1) {
    GEventSock* eventSock = (GEventSock*)arg;
    eventSock->del();
    return;
  }
  buf[readLen] = '\0';
  LOG(INFO) << buf;
}

int main() {
  GSock sock;
  if (!sock.socket(AF_INET, SOCK_STREAM, 0)) { DLOG(ERROR) << lastErr; return -1; }

  GSockAddr sockAddr(AF_INET, 0, INADDR_ANY);
  if (!sock.bind(&sockAddr)) { DLOG(ERROR) << lastErr; return -1; }

  sockAddr.init(AF_INET, htons(10065), htonl(0x7F000001));
  if (!sock.connect(&sockAddr)) { DLOG(ERROR) << lastErr; return -1; }

  GEventBase eventBase;
  GEventSock eventSock;
  eventSock.setEventBase(&eventBase).setFd((int)sock).setCallback(callback).create();
  eventSock.add();
  eventBase.dispatch();
}

