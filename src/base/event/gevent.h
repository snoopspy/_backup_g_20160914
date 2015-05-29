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

#include <event2/util.h>
#include "geventbase.h"

// ----------------------------------------------------------------------------
// GEvent
// ----------------------------------------------------------------------------
struct GEvent {
  GEvent(GEventBase* eventBase) : eventBase_(eventBase), event_(nullptr) {}
  virtual ~GEvent();

  int add(const struct timeval *timeout = nullptr) {
    return event_add(event_, timeout);
  }

  int del() {
    return event_del(event_);
  }

protected:
  virtual void callBack(evutil_socket_t fd, short event) = 0;

protected:
  GEventBase* eventBase_; // reference
  struct event* event_; // created and deleted in descendant class

protected:
  static void _callBack(evutil_socket_t fd, short event, void* arg) {
    GEvent* _event = (GEvent*)arg;
    _event->callBack(fd, event);
  }
};
