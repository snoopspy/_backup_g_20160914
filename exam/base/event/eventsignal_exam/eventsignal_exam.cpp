#include <csignal>
#include <glog/logging.h>
#include <GEventSignal>

struct MyEventSignal : GEventSignal {
  MyEventSignal(GEventBase* eventBase, int signum) :
    GEventSignal(eventBase, signum) {}

protected:
  void callBack(evutil_socket_t fd, short event) override {
    DLOG(INFO) << "fd=" << fd << " event=" << event;
  }
};

int main() {
  GEventBase eventBase;
  MyEventSignal eventSignal(&eventBase, SIGINT);
  eventBase.dispatch();
}
