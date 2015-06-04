// ----------------------------------------------------------------------------
// GTEST
// ----------------------------------------------------------------------------
#ifdef GTEST
#include <gtest/gtest.h>
#include "gerr.h"

TEST(GErr, okTest) {
  errno = 0;
  GLastErr lastErr;
  std::clog << lastErr << std::endl;
  EXPECT_TRUE(lastErr.code() == g::OK);
}

TEST(GErr, nullTest) {
  GLastErr* lastErr = nullptr;
  std::clog << lastErr << std::endl;
}

#endif // GTEST
