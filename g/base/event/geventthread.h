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
#include "g/base/event/geventbase.h"
#include <QThread>

// ----------------------------------------------------------------------------
// GEventThread
// ----------------------------------------------------------------------------
struct GEventThread : QThread {
  GEventBase eventBase_;

protected:
  void run() {
    DLOG(INFO) << "beg run";
    eventBase_.dispatch();
    DLOG(INFO) << "end run";
  }
};
