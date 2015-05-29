#include <csignal>
#include <glog/logging.h>
#include <GEventSignal>

struct MyEventSignal : GEventSignal {
  MyEventSignal(GEventBase* eventBase, int signum) :
    GEventSignal(eventBase, signum) {}
protected:
  void callBack(evutil_socket_t fd, short event) override {
    DLOG(INFO) << "fd=" << fd << " event=" << event;
    if (++called >= 3)
      del();
  }

protected:
  int called = 0;
};

int main() {
  GEventBase eventBase;
  MyEventSignal eventSignal(&eventBase, SIGINT);
  eventSignal.add();
  eventBase.dispatch();
}
