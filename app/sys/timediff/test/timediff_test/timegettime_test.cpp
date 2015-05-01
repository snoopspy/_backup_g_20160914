#ifdef _WIN32

#include <GTimeDiffTimeGetTime>
#include "mytest.h"

TEST(TimeGetTime, test) {
  MyTest<GTimeDiffTimeGetTime>();
}

#endif // _WIN32
