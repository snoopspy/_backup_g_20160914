#include "geventthread.h"

// ----------------------------------------------------------------------------
// GEventThread
// ----------------------------------------------------------------------------
void GEventThread::run() {
  while (true) {
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
