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
// GEventSignal
// ----------------------------------------------------------------------------
struct GEventSignal : GEvent {
  GEventSignal();
  ~GEventSignal() override;
};
