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

#include "gevent.h"

// ----------------------------------------------------------------------------
// GEventTimer
// ----------------------------------------------------------------------------
struct GEventTimer : GEvent {
  GEventTimer(GEventBase* eventBase, bool persist = false);
  ~GEventTimer() override;
};
