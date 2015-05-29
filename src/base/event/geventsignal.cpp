#include <glog/logging.h>
#include "geventsignal.h"

// ----------------------------------------------------------------------------
// GEventSignal
// ----------------------------------------------------------------------------
GEventSignal::GEventSignal(GEventBase* eventBase, int signum) : GEvent(eventBase) {
  DLOG(INFO) << "GEventSignal::GEventSignal()";
  event_ = event_new(eventBase_->get(), signum, EV_SIGNAL | EV_PERSIST, _callBack, this);
}

GEventSignal::~GEventSignal() {
  DLOG(INFO) << "~GEventSignal::GEventSignal()";
  if (event_ != nullptr) {
    event_free(event_);
    event_ = nullptr;
  }
}
