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

#include "gnet.h"
#include "gsock.h"

// ----------------------------------------------------------------------------
// GNetServer
// ----------------------------------------------------------------------------
struct GNetServer : GNet {
  Q_OBJECT
  Q_PROPERTY(int family MEMBER family_)
  Q_PROPERTY(QString localIp MEMBER localIp_)
  Q_PROPERTY(quint16 port MEMBER port_)

public:
  GNetServer(GObj *parent = nullptr) : GNet(parent) {}

  int family_{AF_UNSPEC};
  QString localIp_;
  quint16 port_{0};
};
