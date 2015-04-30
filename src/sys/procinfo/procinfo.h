#pragma once

#include <cstdint>
#include <string>
#include <unistd.h>

class GProcInfo {
public:
  GProcInfo& load(pid_t pid = 0);
  int64_t vm() {
    return (int64_t)vsize_ / 1024;
  }
  int64_t rss() {
    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
    return rss_ * page_size_kb;
  }

public:
  pid_t pid_;
  std::string comm_;
  std::string state_;
  uint64_t ppid_;
  uint64_t pgrp_;
  uint64_t session_;
  uint64_t tty_nr_;
  uint64_t tpgid_;
  uint64_t flags_;
  uint64_t minflt_;
  uint64_t cminflt_;
  uint64_t majflt_;
  uint64_t cmajflt_;
  uint64_t utime_;
  uint64_t stime_;
  uint64_t cutime_;
  uint64_t cstime_;
  uint64_t priority_;
  uint64_t nice_;
  uint64_t O_;
  uint64_t itrealvalue_;
  uint64_t starttime_;
  uint64_t vsize_;
  uint64_t rss_;
};
