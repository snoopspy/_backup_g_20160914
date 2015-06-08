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

#include "g/base/gioobj.h"
#include "gsock.h"

// ----------------------------------------------------------------------------
// GTcpSession
// ----------------------------------------------------------------------------
struct GTcpSession : GIOObj {
public:
  GTcpSession(GObj *parent = nullptr) : GIOObj(parent) {}

  ssize_t read(char *buf, ssize_t len) override;
  ssize_t write(const char *buf, ssize_t len) override;

  GSock sock_;
};
