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
    evutil_socket_t fd,
    event_callback_fn callback,
    Options options = EV_SIGNAL | EV_PERSIST,
    void* arg = nullptr)
    : GEvent(eventBase, fd, options, callback, arg) {}
};
