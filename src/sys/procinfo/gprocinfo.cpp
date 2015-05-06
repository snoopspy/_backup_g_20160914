#include <iostream>
#include <fstream>
#include <string.h>
#include "gprocinfo.h"

GProcInfo& GProcInfo::load(pid_t pid) {
  std::string pid_str = pid == 0 ? "self" : std::to_string(pid);
  std::string file_name = "/proc/" + pid_str + "/stat";

  std::ifstream stat_stream(file_name.c_str(), std::ios_base::in);

  stat_stream >> pid_;
  stat_stream >> comm_;
  stat_stream >> state_;
  stat_stream >> ppid_;
  stat_stream >> pgrp_;
  stat_stream >> session_;
  stat_stream >> tty_nr_;
  stat_stream >> tpgid_;
  stat_stream >> flags_;
  stat_stream >> minflt_;
  stat_stream >> cminflt_;
  stat_stream >> majflt_;
  stat_stream >> cmajflt_;
  stat_stream >> utime_;
  stat_stream >> stime_;
  stat_stream >> cutime_;
  stat_stream >> cstime_;
  stat_stream >> priority_;
  stat_stream >> nice_;
  stat_stream >> O_;
  stat_stream >> itrealvalue_;
  stat_stream >> starttime_;
  stat_stream >> vsize_;
  stat_stream >> rss_;

  stat_stream.close();

  return *this;
}
