#include <iostream>

static const int LOOP_CNT = 1000000;

#ifdef _WIN32

#include <windows.h>
void gettickcount_msec_test() {
  DWORD beg = GetTickCount();
  DWORD end;
  DWORD diff;
  for (int i = 0; i < LOOP_CNT; i++) {
    end = GetTickCount();
    diff = end - beg;
  }
  std::cout << diff << "\t" << __func__ << std::endl;
}

#include <mmsystem.h>
void timegettime_msec_test() {
  DWORD beg = timeGetTime();
  DWORD end;
  DWORD diff;
  for (int i = 0; i < LOOP_CNT; i++) {
    end = timeGetTime();
    diff = end - beg;
  }
  std::cout << diff << "\t" << __func__ << std::endl;
}
#endif // _WIN32

#ifdef __GNUC__
// ----------------------------------------------------------------------------
// gnuc
// ----------------------------------------------------------------------------
#include <time.h>
void clock_usec_test() {
  clock_t beg = clock();
  clock_t end;
  clock_t diff;
  for (int i = 0; i < LOOP_CNT; i++) {
    end = clock();
    diff = end - beg;
  }
  std::cout << diff * 1000 / CLOCKS_PER_SEC << "\t" << __func__ << std::endl;
}

#include <time.h>
void time_sec_test() {
  time_t beg; time(&beg);
  time_t end;
  time_t diff;
  for (int i = 0; i < LOOP_CNT; i++) {
    time(&end);
    diff = end - beg;
  }
  std::cout << diff * 1000 << "\t" << __func__ << std::endl;
}

#include <sys/time.h>
void gettimeofday_usec_test() {
  struct timeval beg; gettimeofday(&beg, NULL);
  struct timeval end;
  long diff;
  for (int i = 0; i < LOOP_CNT; i++) {
    gettimeofday(&end, NULL);
    diff = (end.tv_sec - beg.tv_sec) * 1000000 + (end.tv_usec - beg.tv_usec);
  }
  std::cout << diff / 1000 << "\t" << __func__ << std::endl;
}

#include <time.h>
void clock_gettime_nsec_test() {
  struct timespec beg; clock_gettime(CLOCK_MONOTONIC, &beg);
  struct timespec end;
  long diff;
  for (int i = 0; i < LOOP_CNT; i++) {
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = (end.tv_sec - beg.tv_sec) * 1000000000 + (end.tv_nsec - beg.tv_nsec);
  }
  std::cout << diff / 1000000 << "\t" << __func__ << std::endl;
}
#endif // __GNUC__

// ----------------------------------------------------------------------------
// c++11
// ----------------------------------------------------------------------------
#include <chrono>
void system_clock_msec_test() {
  using namespace std::chrono;

  system_clock::time_point beg = system_clock::now();
  system_clock::time_point end;
  milliseconds diff;
  for (int i = 0; i < LOOP_CNT; i++) {
    end = system_clock::now();
    diff = duration_cast<milliseconds>(end - beg);
  }
  std::cout << diff.count() << "\t" << __func__ << std::endl;
}

#include <chrono>
void system_clock_usec_test() {
  using namespace std::chrono;

  system_clock::time_point beg = system_clock::now();
  system_clock::time_point end;
  microseconds diff;
  for (int i = 0; i < LOOP_CNT; i++) {
    end = system_clock::now();
    diff = duration_cast<microseconds>(end - beg);
  }
  std::cout << diff.count() / 1000 << "\t" << __func__ << std::endl;
}

#include <chrono>
void system_clock_nsec_test() {
  using namespace std::chrono;

  system_clock::time_point beg = system_clock::now();
  system_clock::time_point end;
  nanoseconds diff;
  for (int i = 0; i < LOOP_CNT; i++) {
    end = system_clock::now();
    diff = duration_cast<nanoseconds>(end - beg);
  }
  std::cout << diff.count() / 1000000 << "\t" << __func__ << std::endl;
}

#include <chrono>
void high_resolution_clock_msec_test() {
  using namespace std::chrono;

  high_resolution_clock::time_point beg = high_resolution_clock::now();
  high_resolution_clock::time_point end;
  milliseconds diff;
  for (int i = 0; i < LOOP_CNT; i++) {
    end = high_resolution_clock::now();
    diff = duration_cast<milliseconds>(end - beg);
  }
  std::cout << diff.count() << "\t" << __func__ << std::endl;
}

#include <chrono>
void high_resolution_clock_usec_test() {
  using namespace std::chrono;

  high_resolution_clock::time_point beg = high_resolution_clock::now();
  high_resolution_clock::time_point end;
  microseconds diff;
  for (int i = 0; i < LOOP_CNT; i++) {
    end = high_resolution_clock::now();
    diff = duration_cast<microseconds>(end - beg);
  }
  std::cout << diff.count() / 1000 << "\t" << __func__ << std::endl;
}

#include <chrono>
void high_resolution_clock_nsec_test() {
  using namespace std::chrono;

  high_resolution_clock::time_point beg = high_resolution_clock::now();
  high_resolution_clock::time_point end;
  nanoseconds diff;
  for (int i = 0; i < LOOP_CNT; i++) {
    end = high_resolution_clock::now();
    diff = duration_cast<nanoseconds>(end - beg);
  }
  std::cout << diff.count() / 1000000 << "\t" << __func__ << std::endl;
}

#ifdef QT_CORE_LIB
// ----------------------------------------------------------------------------
// qt
// ----------------------------------------------------------------------------
#include <QTime>
void qtime_msec_test() {
  QTime time;
  time.start();

  int beg = time.elapsed();
  int end;
  int diff;
  for (int i = 0; i < LOOP_CNT; i++) {
    end = time.elapsed();
    diff = end - beg;
  }
  std::cout << diff << "\t" << __func__ << std::endl;
}

#include <QElapsedTimer>
void qelapsedtimer_msec_test() {
  QElapsedTimer elapsedTimer;
  elapsedTimer.start();

  quint64 beg = elapsedTimer.elapsed();
  quint64 end;
  quint64 diff;
  for (int i = 0; i < LOOP_CNT; i++) {
    end = elapsedTimer.elapsed();
    diff = end - beg;
  }
  std::cout << diff << "\t" << __func__ << std::endl;
}

#include <QElapsedTimer>
void qelapsedtimer_nsec_test() {
  QElapsedTimer elapsedTimer;
  elapsedTimer.start();

  quint64 beg = elapsedTimer.nsecsElapsed();
  quint64 end;
  quint64 diff;
  for (int i = 0; i < LOOP_CNT; i++) {
    end = elapsedTimer.nsecsElapsed();
    diff = end - beg;
  }
  std::cout << diff /1000000 << "\t" << __func__ << std::endl;
}
#endif // QT_CORE_LIB

// ----------------------------------------------------------------------------
// main
// ----------------------------------------------------------------------------
int main() {
#ifdef WIN32
  //
  // windows
  //
  gettickcount_msec_test();
  timegettime_msec_test();
#endif // WIN32

#ifdef __GNUC__
  //
  // gnuc
  //
  clock_usec_test();
  time_sec_test();
  gettimeofday_usec_test();
  clock_gettime_nsec_test();
#endif

  //
  // c++11
  //
  system_clock_msec_test();
  system_clock_usec_test();
  system_clock_nsec_test();
  high_resolution_clock_msec_test();
  high_resolution_clock_usec_test();
  high_resolution_clock_nsec_test();

#ifdef QT_CORE_LIB
  //
  // qt
  //
  qtime_msec_test();
  qelapsedtimer_msec_test();
  qelapsedtimer_nsec_test();
#endif // QT_CORE_LIB
}
