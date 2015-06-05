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

#ifdef _WIN32

#include <windows.h>
#include "gtimediff.h"

// ----------------------------------------------------------------------------
// GTimeDiffGetTickCount_
// ----------------------------------------------------------------------------
namespace GTimeDiffGetTickCount_ {
  typedef int Milestone;

  typedef DWORD Clock;

  typedef DWORD Diff;

  struct Timer {
    Clock now() { return GetTickCount(); }
  };
}

// ----------------------------------------------------------------------------
// GTimeDiffGetTickCount
// ----------------------------------------------------------------------------
typedef GTimeDiff<
  GTimeDiffGetTickCount_::Milestone,
  GTimeDiffGetTickCount_::Clock,
  GTimeDiffGetTickCount_::Diff,
  GTimeDiffGetTickCount_::Timer
> GTimeDiffGetTickCount;

#endif // _WIN32
