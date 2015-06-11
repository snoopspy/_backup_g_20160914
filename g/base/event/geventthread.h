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

#include "geventbase.h"
#include "g/base/gthread.h"

// ----------------------------------------------------------------------------
// GEventThread
// ----------------------------------------------------------------------------
struct GEventThread : GThread {
  bool close(bool wait = true) override;

  GEventBase eventBase_;
  bool terminateOnNoEvents_{false};
  unsigned long noEventTimeout{1000}; // msec

protected:
  void run() override;
};
