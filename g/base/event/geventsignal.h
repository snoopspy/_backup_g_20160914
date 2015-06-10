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
  GEventSignal(
    GEventBase* eventBase,
    evutil_socket_t signum,
    event_callback_fn callback,
    void* arg = nullptr,
    Options options = EV_SIGNAL | EV_PERSIST)
    : GEvent(eventBase, signum, options, callback, arg) {}
};
