#include "gstr.h"

std::ostream& operator << (std::ostream& os, QString s) {
  os << s.toStdString();
  return os;
}

// ----------------------------------------------------------------------------
// GTEST
// ----------------------------------------------------------------------------
#ifdef GTEST
#include <gtest/gtest.h>

TEST(GStr, test) {
  QString qs = "hello world";
  std::cout << qs << std::endl;
}

#endif // GTEST
