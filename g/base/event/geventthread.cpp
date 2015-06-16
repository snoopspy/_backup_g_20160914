#include <glog/logging.h> // gilgil temp 2015.06.16
#include "geventthread.h"

// ----------------------------------------------------------------------------
// GEventThread
// ----------------------------------------------------------------------------
static void timerCallback(evutil_socket_t, short, void *) {
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
  if (!GThread::close(wait))
    return false;
  int res = eventBase_.loopbreak();
  //event_base_loopexit(eventBase_.get(), &tv);
  DLOG(INFO) << "loopbreak return " << res; // gilgil temp 2015.06.16

  if (createTimer_) {
    eventTimer_->del();
    delete eventTimer_;
    eventTimer_ = nullptr;
  }
  return res == 0;
}

void GEventThread::run() {
  //eventBase_ = new GEventBase;
  DLOG(INFO) << "stt run " << objectName().toStdString(); // gilgil temp 2015.06.16
  while (active()) {
    DLOG(INFO) << "bef loop " << objectName().toStdString(); // gilgil temp 2015.06.16
    //int res = eventBase_.dispatch();
    int res = eventBase_.loop(EVLOOP_ONCE);
    //struct timeval tv{1, 0};
    //int res = event_base_loopexit(eventBase_.get(), &tv);
    //eventBase_.dispatch()
    DLOG(INFO) << "aft loop " << objectName().toStdString() << " return " << res; // gilgil temp 2015.06.16
    if (res == 1) // no events
    {
      QThread::msleep(timeout);
    }
  }
  DLOG(INFO) << "end run " << objectName().toStdString(); // gilgil temp 2015.06.16
  //delete eventBase_;
}
