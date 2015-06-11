#include "gthread.h"

bool GThread::open() {
  active_ = true;
  QThread::start();
  return true;
}

bool GThread::close(bool wait) {
  bool res = true;
  active_ = false;
  if (wait)
    res = QThread::wait();
  return res;
}
