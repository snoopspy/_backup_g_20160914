#include "gerr.h"

// ----------------------------------------------------------------------------
// GErr
// ----------------------------------------------------------------------------
std::ostream& operator << (std::ostream& os, GErr& err) {
  os << err.name() << ":" << (err.msg().empty() ? "no msg" : err.msg()) << " code=" << err.code();
  return os;
}

std::ostream& operator << (std::ostream& os, GErr&& err) {
  return operator << (os, err);
}

std::ostream& operator << (std::ostream& os, GErr* err) {
  if (err == nullptr) {
    os << "err is null";
    return os;
  }
  return operator << (os, *err);
}

// ----------------------------------------------------------------------------
// GTEST
// ----------------------------------------------------------------------------
#ifdef GTEST
#include <gtest/gtest.h>

TEST(GErr, lastErrTest) {
  int lastErrIdx = EHWPOISON;
  for (int n = 0; n <= lastErrIdx + 10; n++) {
    errno = n;
    GLastErr lastErr;
    std::clog << lastErr << std::endl;
    EXPECT_TRUE(lastErr.code() == n);
  }
}

TEST(GErr, stdErrTest) {
  GStdErr stdErr(g::NOT_SUPPORTED, "not supported");
  std::clog << stdErr << std::endl;
}

TEST(GErr, nullTest) {
  GLastErr* lastErr = nullptr;
  std::clog << lastErr << std::endl;
}

#endif // GTEST
