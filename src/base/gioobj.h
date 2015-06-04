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
};
