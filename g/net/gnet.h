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
#include "gsock.h"

// ----------------------------------------------------------------------------
// GNet
// ----------------------------------------------------------------------------
struct GNet : GObj {
  Q_OBJECT
  Q_PROPERTY(int family MEMBER family_)
  Q_PROPERTY(bool nonBlock MEMBER nonBlock_)

public:
  GNet(GObj* parent = nullptr) : GObj(parent) {}

  GSock bind(int sockType, QString ip, QString port, bool reuseAddr);
  bool connect(GSock sock, int sockType, QString host, QString port);

  int family_{AF_UNSPEC};
  bool nonBlock_{false};
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
