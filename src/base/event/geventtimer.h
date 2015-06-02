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
  GEventTimer(GEventBase* eventBase, bool persist = false) : GEvent(eventBase) {
    DLOG(INFO) << "GEventTimer::GEventTimer()";
    short events = persist ? EV_PERSIST : 0;
    event_ = event_new(eventBase_->get(), -1, events, _callBack, this);
  }

  ~GEventTimer() override {
    DLOG(INFO) << "~GEventTimer::GEventTimer()";
    if (event_ != nullptr) {
      event_free(event_);
      event_ = nullptr;
    }
  }

};
