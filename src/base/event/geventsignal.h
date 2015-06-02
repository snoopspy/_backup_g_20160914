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
// GEventSignal
// ----------------------------------------------------------------------------
struct GEventSignal : GEvent {
  GEventSignal() : GEvent() {}
  GEventSignal(GEventBase* eventBase) : GEvent(eventBase) {}

  bool create(int signum, Options options, event_callback_fn callback, void* arg = nullptr) {
    if (arg == nullptr) arg = this;
    return GEvent::create(signum, EV_SIGNAL | options, callback, arg);
  }
};
