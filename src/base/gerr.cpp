#include <cstring>
#include "gerr.h"

// ----------------------------------------------------------------------------
// GErr
// ----------------------------------------------------------------------------
std::string GErr::msg() {
  if (!msg_.empty()) return msg_;
  return strerror(code_);
}

std::ostream& operator << (std::ostream& os, GErr& err) {
  os << err.msg() << " code=" << err.code();
  return os;
}
