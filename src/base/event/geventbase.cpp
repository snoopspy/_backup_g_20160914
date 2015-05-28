#include "geventbase.h"

// ----------------------------------------------------------------------------
// GEventBase
// ----------------------------------------------------------------------------
GEventBase::GEventBase() {
  base_ = event_base_new();
}

GEventBase::~GEventBase() {
  if (base_ != nullptr) {
    event_base_free(base_);
    base_ = nullptr;
  }
}

int GEventBase::dispatch() {
  return event_base_dispatch(base_);
}
