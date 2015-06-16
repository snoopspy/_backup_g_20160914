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

#include <sys/socket.h>
#include "g/base/gobj.h"

// ----------------------------------------------------------------------------
// GNet
// ----------------------------------------------------------------------------
struct GNet : GObj {
  GNet(GObj *parent = nullptr) : GObj(parent) {}
};

// ----------------------------------------------------------------------------
// GNetErr
// ----------------------------------------------------------------------------
namespace g {
  enum {
    PORT_NOT_SPECIFIED = NET_CATEGORY,
    HOST_NOT_SPECIFIED,
    FAIL_BIND
  };
}

struct GNetErr : GStdErr {
  GNetErr(int code, QString msg) : GStdErr(code, msg) {}

  const char* name() override { return "NetErr"; }
};
