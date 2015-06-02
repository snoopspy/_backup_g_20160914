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

  GEvent() {
    event_ = nullptr;
    eventBase_ = nullptr;
    fd_ = -1;
    options_ = EV_PERSIST;
    callback_ = nullptr;
    arg_ = this;
  }

  virtual ~GEvent() {
    destroy();
  }

  struct event* get() { return event_; }
  GEventBase* eventBase() { return eventBase_; }
  GEvent& setEventBase(GEventBase* eventBase) { eventBase_ = eventBase; return *this; }
  evutil_socket_t fd() { return fd_; }
  GEvent& setFd(evutil_socket_t fd) { fd_ = fd; return *this; }
  Options options() { return options_; }
  GEvent& setOptions(Options options) { options_ = options; return *this; }
  event_callback_fn callback() { return callback_; }
  GEvent& setCallback(event_callback_fn callback) { callback_ = callback; return *this; }
  void* arg() { return arg_; }
  GEvent& setArg(void* arg) { arg_ = arg; return *this; }

  bool create() {
    assert(eventBase_ != nullptr);
    event_ = event_new(eventBase_->get(), fd_, (short)options_, callback_, arg_);
    return event_ != nullptr;
  }

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

  int del() {
    assert(event_ != nullptr);
    return event_del(event_);
  }

protected:
  struct event* event_;
  GEventBase* eventBase_;
  evutil_socket_t fd_;
  Options options_;
  event_callback_fn callback_;
  void* arg_;
};
