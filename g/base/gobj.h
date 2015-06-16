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
#include "gerr.h"

// ----------------------------------------------------------------------------
// GObj
// ----------------------------------------------------------------------------
struct GObj : QObject {
  GObj(GObj *parent = nullptr) : QObject(parent) {}
  ~GObj() override;

  virtual bool open();
  virtual bool close();

  GErr* err{nullptr};
};

// ----------------------------------------------------------------------------
// SET_ERR
// ----------------------------------------------------------------------------
#define SET_ERR(VALUE) if (err != nullptr) delete err; err = new VALUE; LOG(ERROR) << err;
