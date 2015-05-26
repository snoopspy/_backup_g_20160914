#include <cstring>
#include "gerr.h"

// ----------------------------------------------------------------------------
// GErr
// ----------------------------------------------------------------------------
std::ostream& operator << (std::ostream& os, GErr& err) {
  os << err.msg() << " code=" << err.code();
  return os;
}
