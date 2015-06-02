// ----------------------------------------------------------------------------
//
// G Library
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#pragma once

#include <glog/logging.h>
#include "gevent.h"

// ----------------------------------------------------------------------------
// GEventTimer
// ----------------------------------------------------------------------------
struct GEventTimer : GEvent {
  GEventTimer() : GEvent() {}
  GEventTimer(GEventBase* eventBase) : GEvent(eventBase) {}

  bool create(Options options, event_callback_fn callback, void* arg = nullptr) {
    if (arg == nullptr) arg = this;
    return GEvent::create(options, callback, arg);
  }
};
