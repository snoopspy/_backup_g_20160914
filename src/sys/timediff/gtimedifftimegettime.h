// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.1
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_PERFORMANCE_TIME_GET_TIME_H__
#define __V_PERFORMANCE_TIME_GET_TIME_H__

#ifdef _WIN32

#include <windows.h>
#include "gtimediff.h"

// ----------------------------------------------------------------------------
// GTimeDiffTimeGetTime_
// ----------------------------------------------------------------------------
namespace GTimeDiffTimeGetTime_
{
  typedef int Milestone;

  typedef DWORD Clock;

  typedef DWORD Diff;

  struct Timer
  {
    Clock now() { return timeGetTime(); }
  };
}

// ----------------------------------------------------------------------------
// GTimeDiffTimeGetTime
// ----------------------------------------------------------------------------
typedef GTimeDiff<
  GTimeDiffTimeGetTime_::Milestone,
  GTimeDiffTimeGetTime_::Clock,
  GTimeDiffTimeGetTime_::Diff,
  GTimeDiffTimeGetTime_::Timer
> GTimeDiffTimeGetTime;

#endif // _WIN32

#endif // __V_PERFORMANCE_TIME_GET_TIME_H__
