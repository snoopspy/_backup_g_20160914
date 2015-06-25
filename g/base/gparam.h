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

#include <QStringList>
#include "gobj.h"

// ----------------------------------------------------------------------------
// GParam
// ----------------------------------------------------------------------------
struct GParam final {
  GParam(int argc, char* argv[]);
  ~GParam();

  void help(GObj* obj);
  void parse(GObj* obj);

  QStringList argv_;
};
