#include <glog/logging.h>
#include "gevent.h"

// ----------------------------------------------------------------------------
// GEvent
// ----------------------------------------------------------------------------
GEvent::~GEvent() {
  if (event_ == nullptr) {
    LOG(WARNING) << "event is not null(" << (void*)event_ << ")";
  }
}
