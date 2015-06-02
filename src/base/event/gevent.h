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

#include <cassert>
#include <event2/util.h>
#include "geventbase.h"

// ----------------------------------------------------------------------------
// GEvent
// ----------------------------------------------------------------------------
struct GEvent {
  typedef short Option;
  typedef short Options;

  GEvent() : eventBase_(nullptr), event_(nullptr) {}
  GEvent(GEventBase* eventBase) : eventBase_(eventBase), event_(nullptr) {}
  virtual ~GEvent() { destroy(); }

  struct event* get() { return event_; }
  GEventBase* eventBase() { return eventBase_; }
  void setEventBase(GEventBase* eventBase) { eventBase_ = eventBase; }

protected:
  bool create(evutil_socket_t fd, Options options, event_callback_fn callback, void* arg) {
    assert(eventBase_ != nullptr);
    event_ = event_new(eventBase_->get(), fd, (short)options, callback, arg);
    return event_ != nullptr;
  }

  bool create(Options options, event_callback_fn callback, void* arg) {
    return create(-1, options, callback, arg);
  }

public:
  void destroy() {
    if (event_ != nullptr) {
      event_free(event_);
      event_ = nullptr;
    }
  }

  int add() {
    assert(event_ != nullptr);
    return event_add(event_, nullptr);
  }

  int add(const struct timeval timeout) {
    assert(event_ != nullptr);
    return event_add(event_, &timeout);
  }

  //
  // del
  //
  int del() {
    return event_del(event_);
  }

protected:
  GEventBase* eventBase_; // reference
  struct event* event_;
};
