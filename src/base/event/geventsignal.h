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
  GEventSignal(GEventBase* eventBase, int signum) : GEvent(eventBase) {
    DLOG(INFO) << "GEventSignal::GEventSignal()";
    event_ = event_new(eventBase_->get(), signum, EV_SIGNAL | EV_PERSIST, _callBack, this);
  }

  ~GEventSignal() override {
    DLOG(INFO) << "~GEventSignal::GEventSignal()";
    if (event_ != nullptr) {
      event_free(event_);
      event_ = nullptr;
    }
  }
};
