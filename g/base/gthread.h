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
  GThread(QObject* parent = nullptr) : QThread(parent) {}

  bool active() { return active_; }

  virtual bool open() {
    active_ = true;
    QThread::start();
    return true;
  }

  virtual bool close(bool wait = true) {
    bool res = true;
    active_ = false;
    if (wait)
      res = QThread::wait();
    return res;
  }

private:
  bool active_{false};
};
