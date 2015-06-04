#include <cstring>
#include "gerr.h"

// ----- gilgil temp 2015.06.04 -----
/*
// ----------------------------------------------------------------------------
// GErr
// ----------------------------------------------------------------------------
std::string GErr::msg() {
  if (!msg_.empty()) return msg_;

  //
  // linux error code(EHWPOISON: maximum of linux error code)
  //
  if (code_ > 0 && code_ <= EHWPOISON)
    return strerror(code_);

  return "UNKNOWN";
}
thread_local GErr lastErr;
*/

// ----------------------------------

std::ostream& operator << (std::ostream& os, GErr& err) {
  os << err.name() << ":" << err.msg() << " code=" << err.code();
  return os;
}

