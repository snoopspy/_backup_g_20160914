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

#include "base/gobj.h"

// ----------------------------------------------------------------------------
// GIOObj
// ----------------------------------------------------------------------------
class GIOObj : public GObj {
public:
  GIOObj(GIOObj *parent = nullptr) : GObj(parent) {}
  virtual qint64 readData(char *data, qint64 maxlen) = 0;
  virtual qint64 readLineData(char *data, qint64 maxlen);
  virtual qint64 writeData(const char *data, qint64 len) = 0;
};
