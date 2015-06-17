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

#include <QThread>

// ----------------------------------------------------------------------------
// GThread
// ----------------------------------------------------------------------------
struct GThread : QThread {
  bool active() { return active_; }

  virtual bool open();
  virtual bool close(bool wait = true);

private:
  bool active_{false};
};
