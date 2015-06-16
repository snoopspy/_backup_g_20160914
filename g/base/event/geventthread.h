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
#include "geventtimer.h"
#include "g/base/gthread.h"

// ----------------------------------------------------------------------------
// GEventThread
// ----------------------------------------------------------------------------
struct GEventThread : GThread {
  ~GEventThread() override;
  bool open() override;
  bool close(bool wait = true) override;

  GEventBase eventBase_;
  bool createTimer_{true};
  unsigned long timeout{1000}; // msec

protected:
  GEventTimer* eventTimer_{nullptr};
  void run() override;
};
