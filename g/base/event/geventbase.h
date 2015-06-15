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

#include <event2/event.h>
#include <glog/logging.h>

// ----------------------------------------------------------------------------
// GEventBase
// ----------------------------------------------------------------------------
struct GEventBase {
  GEventBase() {
    base_ = event_base_new();
  }

  virtual ~GEventBase() {
    if (base_ != nullptr) {
      event_base_free(base_);
      base_ = nullptr;
    }
  }

  struct event_base* get() {
    return base_;
  }

  int dispatch() {
    int res = event_base_dispatch(base_);
    return res;
  }

  int loopbreak() {
    int res = event_base_loopbreak(base_);
    return res;
  }

protected:
  struct event_base *base_;
};
