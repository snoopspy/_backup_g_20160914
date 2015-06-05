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
  GEventTimer(
    GEventBase* eventBase,
    event_callback_fn callback,
    void* arg = nullptr,
    Options options = EV_PERSIST)
    : GEvent(eventBase, -1, options, callback, arg) {}
  ~GEventTimer() {}
};
