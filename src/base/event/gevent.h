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

  virtual ~GEvent() {
    if (event_ != nullptr) {
      LOG(WARNING) << "event is not null(" << (void*)event_ << ")";
    }
  }

  //
  // new
  //

  /*
  @param base the event base to which the event should be attached.
  @param fd the file descriptor or signal to be monitored, or -1.
  @param events desired events to monitor: bitfield of EV_READ, EV_WRITE,
      EV_SIGNAL, EV_PERSIST, EV_ET.
  @param callback callback function to be invoked when the event occurs
  @param callback_arg an argument to be passed to the callback function

  @return a newly allocated struct event that must later be freed with
    event_free().
  @see event_free(), event_add(), event_del(), event_assign()
  struct event *event_new(struct event_base *, evutil_socket_t, short, event_callback_fn, void *);
  */
  struct event_base* base_;
  int fd_;
  short events_;
  event_callback_fn callback_;
  void* callback_arg;

  //
  // free
  //

  //
  // add
  //
  int add() {
    return event_add(event_, nullptr);
  }

  int add(const struct timeval timeout) {
    return event_add(event_, &timeout);
  }

  //
  // del
  //
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
