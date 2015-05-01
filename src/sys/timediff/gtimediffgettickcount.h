// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.1
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_PERFORMANCE_GET_TICK_COUNT_H__
#define __V_PERFORMANCE_GET_TICK_COUNT_H__

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

#endif // __V_PERFORMANCE_GET_TICK_COUNT_H__
