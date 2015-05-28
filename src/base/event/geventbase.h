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

// ----------------------------------------------------------------------------
// GEventBase
// ----------------------------------------------------------------------------
struct GEventBase {
  GEventBase();
  virtual ~GEventBase();

  int dispatch();

protected:
  struct event_base *base_;
};
