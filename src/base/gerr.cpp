#include "gerr.h"

#ifdef GTEST
#include <gtest/gtest.h>

TEST(GErr, test) {
  errno = 0;
  GLastErr lastErr;
  std::clog << lastErr << std::endl;
  EXPECT_TRUE(lastErr.code() == g::OK);
}

#endif // GTEST
