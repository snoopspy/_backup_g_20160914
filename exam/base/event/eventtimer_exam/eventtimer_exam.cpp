#include <glog/logging.h>
#include <GEventTimer>

struct MyEventTimer : GEventTimer {
  MyEventTimer(GEventBase* eventBase, bool persist = false) :
    GEventTimer(eventBase, persist) {}
protected:
  void callBack(evutil_socket_t fd, short event) override {
    DLOG(INFO) << "fd=" << fd << " event=" << event;
    if (++called < 3) {
      struct timeval tv = { 1, 0 };
      add(&tv);
    }
  }

protected:
  int called = 0;
};

int main() {
  GEventBase eventBase;
  MyEventTimer eventTimer(&eventBase);

  struct timeval tv = { 1, 0 };
  eventTimer.add(&tv);
  eventBase.dispatch();
}
