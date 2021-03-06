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

#include <assert.h>
#include <event2/util.h>
#include "geventbase.h"

// ----------------------------------------------------------------------------
// GEvent
// ----------------------------------------------------------------------------
struct GEvent {
  // EV_TIMEOUT 0x01
  // EV_READ    0x02
  // EV_WRITE   0x04
  // EV_SIGNAL  0x08
  // EV_PERSIST 0x10
  // EV_ET      0x20
  typedef short Options;

protected:
  GEvent(
    GEventBase* eventBase,
    evutil_socket_t fd,
    Options options,
    event_callback_fn callback,
    void* arg) {
    if (arg == nullptr) arg = this;
    event_ = event_new(eventBase->get(), fd, options, callback, arg);
  }

public:
  ~GEvent() {
    destroy();
  }

  void destroy() {
    if (event_ != nullptr) {
      event_free(event_);
      event_ = nullptr;
    }
  }

  struct event* get() {
    return event_;
  }

  int add() {
    assert(event_ != nullptr);
    int res = event_add(event_, nullptr);
    return res;
  }

  int add(const struct timeval timeout) {
    assert(event_ != nullptr);
    int res = event_add(event_, &timeout);
    return res;
  }

  int del() {
    assert(event_ != nullptr);
    int res = event_del(event_);
    return res;
  }

protected:
  struct event* event_;
};
