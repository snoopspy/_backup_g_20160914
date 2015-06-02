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
  GEventSock() {
    options_ |= EV_READ;
  }

  bool create() {
    if (fd_ == -1) {
      LOG(WARNING) << "fd_ must not be -1";
    }
    return GEvent::create();
  }
};
