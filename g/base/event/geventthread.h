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
#include <QThread>

// ----------------------------------------------------------------------------
// GEventThread
// ----------------------------------------------------------------------------
struct GEventThread : QThread {
  GEventBase eventBase_;

protected:
  void run() {
    eventBase_.dispatch();
  }
};
