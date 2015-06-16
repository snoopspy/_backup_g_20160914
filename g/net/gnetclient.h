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
// GNetClient
// ----------------------------------------------------------------------------
struct GNetClient : GNet {
  Q_OBJECT
  Q_PROPERTY(int family MEMBER family_)
  Q_PROPERTY(QString localIp MEMBER localIp_)
  Q_PROPERTY(QString localPort MEMBER localPort_)
  Q_PROPERTY(QString host MEMBER host_)
  Q_PROPERTY(QString port MEMBER port_)
  Q_PROPERTY(bool nonBlock MEMBER nonBlock_)

public:
  GNetClient(GObj *parent = nullptr) : GNet(parent) {}

  int family_{AF_UNSPEC};
  QString localIp_;
  QString localPort_;
  QString host_;
  QString port_;
  bool nonBlock_{true};
};
