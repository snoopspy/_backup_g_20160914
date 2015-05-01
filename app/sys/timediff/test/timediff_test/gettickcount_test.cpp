#ifdef _WIN32

#include <GTimeDiffGetTickCount>
#include "mytest.h"

TEST(GetTickCount, test) {
  MyTest<GTimeDiffGetTickCount>();
}

#endif // _WIN32
