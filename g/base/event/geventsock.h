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
// GEventSock
// ----------------------------------------------------------------------------
struct GEventSock : GEvent {
  GEventSock(
    GEventBase* eventBase,
    evutil_socket_t fd,
    event_callback_fn callback,
    void* arg = nullptr,
    Options options = EV_READ | EV_PERSIST)
    : GEvent(eventBase, fd, options, callback, arg) {}
};
