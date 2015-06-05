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

#include <chrono>
#include <ostream>
#include "gtimediff.h"

// ----------------------------------------------------------------------------
// GTimeDiffChrono_
// ----------------------------------------------------------------------------
namespace GTimeDiffChrono_ {
  typedef int Milestone;

  typedef std::chrono::high_resolution_clock::time_point Clock;

  typedef std::chrono::high_resolution_clock::duration Diff;

  typedef std::chrono::high_resolution_clock Timer;
};

// ----------------------------------------------------------------------------
// GTimeDiffChrono
// ----------------------------------------------------------------------------
typedef GTimeDiff<
  GTimeDiffChrono_::Milestone,
  GTimeDiffChrono_::Clock,
  GTimeDiffChrono_::Diff,
  GTimeDiffChrono_::Timer
> GTimeDiffChrono;

std::ostream& operator << (std::ostream& os, std::chrono::high_resolution_clock::duration& rhs) {
  os << rhs.count();
  return os;
}
