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

// ----------------------------------------------------------------------------
// GNetServer
// ----------------------------------------------------------------------------
struct GNetServer : GNet {
  Q_OBJECT
  Q_PROPERTY(QString localIp MEMBER localIp_)
  Q_PROPERTY(QString port MEMBER port_)

public:
  GNetServer(GObj *parent = nullptr) : GNet(parent) {}

  QString localIp_;
  QString port_;
};
