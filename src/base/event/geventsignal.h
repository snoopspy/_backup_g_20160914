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
  GEventSignal() {
    options_ |= EV_SIGNAL;
  }

  bool create() {
    if (fd_ == -1) {
      LOG(WARNING) << "fd_ must not be -1";
    }
    return GEvent::create();
  }
};
