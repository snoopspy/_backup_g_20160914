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
#include "net/gsock.h"

// ----------------------------------------------------------------------------
// GEventSock
// ----------------------------------------------------------------------------
struct GEventSock : GEvent {
  GEventSock() : GEvent() {
    options_ |= EV_READ;
  }
};
