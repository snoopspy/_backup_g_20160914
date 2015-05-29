#include "geventsignal.h"
#include <glog/logging.h>

// ----------------------------------------------------------------------------
// GEventSignal
// ----------------------------------------------------------------------------
GEventSignal::GEventSignal() {
  DLOG(INFO) << "GEventSignal::GEventSignal()";
}

GEventSignal::~GEventSignal() {
  DLOG(INFO) << "~GEventSignal::GEventSignal()";
}
