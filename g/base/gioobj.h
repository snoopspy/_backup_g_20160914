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

#include "gobj.h"

// ----------------------------------------------------------------------------
// GIOObj
// ----------------------------------------------------------------------------
struct GIOObj : GObj {
  GIOObj(GObj *parent = nullptr) : GObj(parent) {}

  virtual ssize_t read(char *buf, ssize_t len) = 0;
  virtual ssize_t write(const char *buf, ssize_t len) = 0;
};
