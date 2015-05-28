#include "geventbase.h"

// ----------------------------------------------------------------------------
// GEventBase
// ----------------------------------------------------------------------------
GEventBase::GEventBase() {
  base_ = event_base_new();
}

GEventBase::~GEventBase() {
  // free base_ // gilgil temp 2015.05.29
}
