// ----------------------------------------------------------------------------
// GTEST
// ----------------------------------------------------------------------------
#ifdef GTEST
#include <gtest/gtest.h>

template <class TIMEDIFF, int LOOP_CNT = 100000>
struct MyTest {
  MyTest() {
    TIMEDIFF td;
    for (int i = 0; i < LOOP_CNT; i++) {
      td.check(1);
      td.check(2);
      td.check(3);
      td.check(4);
      td.check(5);
      td.check(6);
      td.check(7);
      td.check(8);
      td.check(9);
      td.check(10);
      td.check(11);
      td.check(12);
      td.check(13);
      td.check(14);
      td.check(15);
      td.check(16);
      td.check(17);
      td.check(18);
      td.check(19);
      td.check(20);
      td.check(21);
      td.check(22);
      td.check(23);
      td.check(24);
      td.check(25);
      td.check(26);
      td.check(27);
      td.check(28);
      td.check(29);
      td.check(30);
      td.check(31);
      td.check(32);
    }
    td.report();
  }
};

#include "gtimediffchrono.h"
TEST(GTimeDiff, chronoTest) {
  MyTest<GTimeDiffChrono>();
}

#include "gtimediffelapsedtimer.h"
TEST(GTimeDiff, elapsedTimerTest) {
  MyTest<GTimeDiffElapsedTimer>();
}

#ifdef _WIN32
#include "gtimediffgettickcount.h"
TEST(GTimeDiff, getTickCountTest) {
  MyTest<GTimeDiffGetTickCount>();
}
#endif // _WIN32

#include "gtimediffgettimeofday.h"

TEST(GTimeDiff, getTimeOfDayTest) {
  MyTest<GTimeDiffGetTimeOfDay>();
}

#include "gtimediffnull.h"
TEST(GTimeDiff, nullTest) {
  MyTest<GTimeDiffNull>();
}

#ifdef _WIN32
#include "gtimedifftimegettime.h"

TEST(GTimeDiff, TimeGetTimeTest) {
  MyTest<GTimeDiffTimeGetTime>();
}
#endif // _WIN32

#endif // GTEST
