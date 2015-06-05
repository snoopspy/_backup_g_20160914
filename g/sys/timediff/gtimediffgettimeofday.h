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

#include <sys/time.h>
#include "gtimediff.h"

// ----------------------------------------------------------------------------
// GTimeDiffGetTimeOfDay_
// ----------------------------------------------------------------------------
namespace GTimeDiffGetTimeOfDay_ {
  typedef int Milestone;

  typedef long /*__suseconds_t*/ Diff;

  struct Clock {
    struct timeval tv_;

    Diff operator - (const Clock &rhs) const {
      return (tv_.tv_sec - rhs.tv_.tv_sec) * 1000000 + (tv_.tv_usec - rhs.tv_.tv_usec);
    }
  };

  struct Timer {
    Clock now() {
      Clock res;
      gettimeofday(&res.tv_, NULL);
      return res;
    }
  };
};

// ----------------------------------------------------------------------------
// GTimeDiffGetTimeOfDay
// ----------------------------------------------------------------------------
typedef GTimeDiff<
  GTimeDiffGetTimeOfDay_::Milestone,
  GTimeDiffGetTimeOfDay_::Clock,
  GTimeDiffGetTimeOfDay_::Diff,
  GTimeDiffGetTimeOfDay_::Timer
> GTimeDiffGetTimeOfDay;
