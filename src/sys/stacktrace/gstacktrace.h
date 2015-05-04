// ----------------------------------------------------------------------------
//
// G Library
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#pragma once

#include <mutex>
#include <signal.h>
#include <stdio.h>

/*
 * To dump exact stack stats, "-rdynamic" link option should be added.
 */

// ----------------------------------------------------------------------------
// GStracTrace
// ----------------------------------------------------------------------------
class GStackTrace {
private:
  GStackTrace();
  virtual ~GStackTrace();

public:
  void setOutput(FILE* output);
  void setSkipFrames(int skipFrames);
  void setMaxFrames(int maxFrames);
  void setSignal(int signum);
  void unsetSignal();
  void dump();

protected:
  __sighandler_t prev_handler_;
  int signum_;
  FILE* output_;
  int skipFrames_;
  int maxFrames_;
  std::mutex mutex_;

  void printStacktrace();
  static void sighandler(int signum);

public:
  static GStackTrace& instance();
};

