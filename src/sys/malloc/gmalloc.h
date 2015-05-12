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

#include <stddef.h>

// ----------------------------------------------------------------------------
// GMalloc
// ----------------------------------------------------------------------------
class GMalloc {
public:
  static bool init();
  static bool fini();
};
