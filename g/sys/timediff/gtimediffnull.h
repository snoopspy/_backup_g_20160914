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

#include "gtimediff.h"

// ----------------------------------------------------------------------------
// GTimeDiffNull_
// ----------------------------------------------------------------------------
namespace GTimeDiffNull_ {
  typedef int Milestone;

  struct Diff {
    int d_;

    Diff operator += (const Diff &rhs) { d_ += rhs.d_; return *this; }
    Diff operator / (const int count) const { Diff res; res.d_ = d_ / count; return res; }
  };

  struct Clock {
    int c_;

    Diff operator - (const Clock &rhs) const { Diff res; res.d_ = c_ - rhs.c_; return res; }
  };

  struct Timer {
    int t_;

    Clock now() { Clock res; res.c_ = t_++; return res; }
  };
};

std::ostream& operator << (std::ostream& os, GTimeDiffNull_::Diff& rhs) {
  os << rhs.d_;
  return os;
}

// ----------------------------------------------------------------------------
// GTimeDiffNull
// ----------------------------------------------------------------------------
typedef GTimeDiff<
  GTimeDiffNull_::Milestone,
  GTimeDiffNull_::Clock,
  GTimeDiffNull_::Diff,
  GTimeDiffNull_::Timer
> GTimeDiffNull;
