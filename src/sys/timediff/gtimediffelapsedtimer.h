// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.1
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_PERFORMANCE_ELAPSEDTIMER_H__
#define __V_PERFORMANCE_ELAPSEDTIMER_H__

#include <QElapsedTimer>
#include "gtimediff.h"

// ----------------------------------------------------------------------------
// GTimeDiffElapsedTimer_
// ----------------------------------------------------------------------------
namespace GTimeDiffElapsedTimer_ {
  typedef int Milestone;

  typedef qint64 Clock;

  typedef qint64 Diff;

  struct Timer {
    QElapsedTimer elapsedTimer;
    Timer() { elapsedTimer.start(); }
    Clock now() { return elapsedTimer.nsecsElapsed(); }
  };
}

// ----------------------------------------------------------------------------
// GTimeDiffElapsedTimer
// ----------------------------------------------------------------------------
typedef GTimeDiff<
  GTimeDiffElapsedTimer_::Milestone,
  GTimeDiffElapsedTimer_::Clock,
  GTimeDiffElapsedTimer_::Diff,
  GTimeDiffElapsedTimer_::Timer
> GTimeDiffElapsedTimer;

#endif // __V_PERFORMANCE_ELAPSEDTIMER_H__
