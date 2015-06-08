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

#include <QObject>
#include "g/base/gerr.h"

// ----------------------------------------------------------------------------
// GObj
// ----------------------------------------------------------------------------
struct GObj : public QObject {
public:
  GObj(GObj *parent = nullptr) : QObject(parent) {}
  ~GObj() override;

  virtual bool open();
  virtual bool close();

  GErr* err{nullptr};
};
