#include <csignal>
#include <glog/logging.h>
#include <GEventSignal>

static int called = 0;
void callback(evutil_socket_t fd, short events, void* arg) {
  DLOG(INFO) << "fd=" << fd << " event=" << events;
  if (++called >= 3) {
    GEventSignal* eventSignal = (GEventSignal*)arg;
    eventSignal->del();
  }
}

int main() {
  GEventBase eventBase;
  GEventSignal eventSignal(&eventBase);
  eventSignal.create(SIGINT, EV_PERSIST, callback);
  eventSignal.add();
  eventBase.dispatch();
}
