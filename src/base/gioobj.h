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

#include <QIODevice>
#include <GObj>

// ----------------------------------------------------------------------------
// GIOObj
// ----------------------------------------------------------------------------
class GIOObj : public GObj, QIODevice {
public:
  GIOObj(GIOObj *parent = nullptr) : GObj(parent) {}
};
