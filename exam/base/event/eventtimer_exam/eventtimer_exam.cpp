#include <glog/logging.h>
#include <GEventTimer>

static int called = 0;
void callback(evutil_socket_t fd, short events, void* arg) {
  DLOG(INFO) << "fd=" << fd << " event=" << events;
  if (++called >= 3) {
    GEventTimer* eventTimer = (GEventTimer*)arg;
    eventTimer->del();
  }
}

int main() {
  GEventBase eventBase;
  GEventTimer eventTimer;
  eventTimer.setEventBase(&eventBase).setCallback(callback).create();
  eventTimer.add(timeval{1, 0});
  eventBase.dispatch();
}
