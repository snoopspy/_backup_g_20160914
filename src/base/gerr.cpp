#include "gerr.h"

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
