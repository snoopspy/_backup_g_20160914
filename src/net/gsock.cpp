#include "base/gerr.h"
#include "gsock.h"

// ----------------------------------------------------------------------------
// GSock
// ----------------------------------------------------------------------------
GSock::GSock(int domain, int type, int protocol) {
  sock_ = socket(domain, type, protocol);
  if (sock_ == -1) {
    lastErr.set(errno);
  }
}
