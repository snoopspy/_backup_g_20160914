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
  Q_PROPERTY(int sockType MEMBER sockType_)
  Q_PROPERTY(bool nonBlock MEMBER nonBlock_)

public:
  GNet(GObj* parent = nullptr) : GObj(parent) {}

  GSock bind(int sockType, QString ip, QString port, bool reuseAddr);
  bool connect(GSock sock, int sockType, QString host, QString port);
  bool listen(GSock sock, int backLog);

  int family_{AF_UNSPEC}; // AF_UNSPEC(0), AF_INET(2) or AF_INET6(10)
  int sockType_; // SOCK_STREAM(1), SOCK_DGRAM(2) or SOCK_RAW(3)
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
