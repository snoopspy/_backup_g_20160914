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

#include <glog/logging.h>
#include "geventbase.h"
#include <QThread>

// ----------------------------------------------------------------------------
// GEventThread
// ----------------------------------------------------------------------------
struct GEventThread : QThread {
  GEventBase eventBase_;
  bool terminateOnNoEvents_{false};
  unsigned long noEventTimeout{1000}; // msec

protected:
  void run() override;
};
