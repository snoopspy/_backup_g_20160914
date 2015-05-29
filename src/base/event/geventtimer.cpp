#include <glog/logging.h>
#include "geventtimer.h"

// ----------------------------------------------------------------------------
// GEventTimer
// ----------------------------------------------------------------------------
GEventTimer::GEventTimer(GEventBase* eventBase, bool persist) : GEvent(eventBase) {
  DLOG(INFO) << "GEventTimer::GEventTimer()";
  short events = persist ? EV_PERSIST : 0;
  event_ = event_new(eventBase_->get(), -1, events, _callBack, this);
}

GEventTimer::~GEventTimer() {
  DLOG(INFO) << "~GEventTimer::GEventTimer()";
  if (event_ != nullptr) {
    event_free(event_);
    event_ = nullptr;
  }
}
