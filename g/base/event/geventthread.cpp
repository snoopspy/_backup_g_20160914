#include "geventthread.h"

// ----------------------------------------------------------------------------
// GEventThread
// ----------------------------------------------------------------------------
bool GEventThread::close(bool wait) {
  if (!GThread::close(wait))
    return false;
  int res = eventBase_.loopbreak();
  return res == 0;
}

void GEventThread::run() {
  while (active()) {
    int res = eventBase_.dispatch();
    if (res == 0) // succeed
      break;
    else if (res == 1) // no events
    {
      if (terminateOnNoEvents_) break;
      QThread::msleep(noEventTimeout);
    }
  }
}
