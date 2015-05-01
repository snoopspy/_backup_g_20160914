#include <thread>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include <GStackTrace>

void foo1() {
  GStackTrace::instance().dump();
}

void foo2() {
  foo1();
}

void foo3() {
  foo2();
}

TEST(GStackTrace, test) {
  LOG(INFO) << "beg test";
  foo3();
  LOG(INFO) << "aft test";
}

void sleepProc(int n) {
  LOG(INFO) << "beg sleepProc " << n;
  for (int i = 0; i < 5; i++) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  LOG(INFO) << "end sleepProc " << n;
}

TEST(GStackTrace, sleepThreadTest) {
  LOG(INFO) << "beg sleepThreadTest";
  {
    constexpr int THREAD_CNT = 3;
    std::vector<std::thread> threads;
    for (int i = 0; i < THREAD_CNT; i++)
      threads.emplace_back(sleepProc, i);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    GStackTrace::instance().dump();

    for (auto& thread: threads)
      thread.join();
  }
  LOG(INFO) << "end sleepThreadTest";
}

#include <atomic>
namespace SpinLockTest {
  std::atomic_flag lock_ = ATOMIC_FLAG_INIT;
  volatile bool active_ = false;

  void run() {
    while (active_) {
      while (lock_.test_and_set(std::memory_order_acquire)) // acquire lock
           ; // spin
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      lock_.clear(std::memory_order_release); // release lock
    }
  }
};

TEST(GStackTrace, spinLockTest) {
  LOG(INFO) << "beg spinLockTest";
  {
    SpinLockTest::active_ = true;
    static constexpr int THREAD_CNT = 3;
    std::vector<std::thread> threads;
    for (int n = 0; n < THREAD_CNT; ++n) {
      threads.emplace_back(SpinLockTest::run);
    }
    for (int i = 0; i < 10; i++) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      GStackTrace::instance().dump();;
    }

    SpinLockTest::active_ = false;
    for (auto& thread : threads) {
        thread.join();
    }
  }
  LOG(INFO) << "end spinLockTest";
}
