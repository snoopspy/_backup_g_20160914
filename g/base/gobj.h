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
class GObj : public QObject {
public:
  GObj(GObj *parent = nullptr) : QObject(parent) {}

  ~GObj() override {
    if (err != nullptr) {
      delete err;
      err = nullptr;
    }
  }

  GErr* err{nullptr};
};
