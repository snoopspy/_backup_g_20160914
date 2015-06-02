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
  GEventTimer() {
  }

  bool create() {
    if (fd_ == -1) {
      LOG(WARNING) << "fd_ must be -1";
    }
    return GEvent::create();
  }
};
