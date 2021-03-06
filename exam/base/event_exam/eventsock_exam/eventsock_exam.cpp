#include <glog/logging.h>
#include <GErr>
#include <GEventSock>
#include <GSock>

void callback(evutil_socket_t fd, short events, void* arg) {
  DLOG(INFO) << "fd=" << fd << " event=" << events;

  char buf[1024];
  ssize_t readLen = ::recv(fd, buf, 1023, 0);
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
  if (!sock.socket(AF_INET, SOCK_STREAM, 0)) { LOG(ERROR) << GLastErr(); return 1; }

  GSockAddr sockAddr(AF_INET, 0, INADDR_ANY);
  if (!sock.bind(&sockAddr)) { LOG(ERROR) << GLastErr(); return 1; }

  sockAddr.init(AF_INET, htons(10065), htonl(0x7F000001));
  if (!sock.connect(&sockAddr)) { LOG(ERROR) << GLastErr(); return 1; }

  GEventBase eventBase;
  GEventSock eventSock(&eventBase, (int)sock, callback);
  eventSock.add();
  eventBase.dispatch();
}
