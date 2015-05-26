#include <cstring>
#include "gerr.h"

// ----------------------------------------------------------------------------
// GErr
// ----------------------------------------------------------------------------
std::string GErr::msg() {
  if (!msg_.empty()) return msg_;

  //
  // linux error code
  // EHWPOISON is maximum of linux error code
  //
  if (code_ > 0 && code_ <= EHWPOISON)
    return strerror(code_);

  return "UNKNOWN";
}

std::ostream& operator << (std::ostream& os, GErr& err) {
  os << err.msg() << " code=" << err.code();
  return os;
}
