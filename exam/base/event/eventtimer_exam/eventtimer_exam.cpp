#include <glog/logging.h>
#include <GEventTimer>

struct MyEventTimer : GEventTimer {
  MyEventTimer(GEventBase* eventBase, bool persist = false) :
    GEventTimer(eventBase, persist) {}
protected:
  void callBack(evutil_socket_t fd, short event) override {
    DLOG(INFO) << "fd=" << fd << " event=" << event;
    if (++called < 3) {
      add(timeval{1, 0});
    }
  }

protected:
  int called = 0;
};

int main() {
  GEventBase eventBase;
  MyEventTimer eventTimer(&eventBase);

  eventTimer.add(timeval{1, 0});
  eventBase.dispatch();
}
