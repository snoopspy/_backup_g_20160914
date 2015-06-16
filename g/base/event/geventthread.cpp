#include "geventthread.h"

// ----------------------------------------------------------------------------
// GEventThread
// ----------------------------------------------------------------------------
static void timerCallback(evutil_socket_t, short, void *) {
}

GEventThread::~GEventThread() {
  close();
  if (createTimer_) {
    eventTimer_->del();
    delete eventTimer_;
    eventTimer_ = nullptr;
  }
}

bool GEventThread::open() {
  if (createTimer_) {
    eventTimer_ = new GEventTimer(&eventBase_, timerCallback);
    struct timeval tv;
    tv.tv_sec = timeout / 1000;
    tv.tv_usec = (timeout % 1000) * 1000;
    eventTimer_->add(tv);
  }
  bool res = GThread::open();
  return res;
}

bool GEventThread::close(bool wait) {
  if (!GThread::close(false))
    return false;
  int res = eventBase_.loopbreak();
  if (res != 0) {
    LOG(ERROR) << "eventBase_.loopbreak() return " << res;
  }

  // createTimer_ is destroyed in destructor

  if (wait)
    return GThread::wait();
  else
    return true;
}

void GEventThread::run() {
  while (active()) {
    int res = eventBase_.loop(EVLOOP_ONCE);
    if (res == -1) // fail
      break;
    else if (res == 1) // no events
      QThread::msleep(timeout);
  }
}
