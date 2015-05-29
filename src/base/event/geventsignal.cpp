#include "geventsignal.h"
#include <glog/logging.h>

// ----------------------------------------------------------------------------
// GEventSignal
// ----------------------------------------------------------------------------
GEventSignal::GEventSignal(GEventBase* eventBase, int signum) : GEvent(eventBase) {
  DLOG(INFO) << "GEventSignal::GEventSignal()";
  event_ = evsignal_new(eventBase_->get(), signum, _callBack, this);
}

GEventSignal::~GEventSignal() {
  DLOG(INFO) << "~GEventSignal::GEventSignal()";
}
