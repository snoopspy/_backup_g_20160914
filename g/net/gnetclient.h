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
  Q_PROPERTY(quint16 localPort MEMBER localPort_)
  Q_PROPERTY(QString host MEMBER host_)
  Q_PROPERTY(quint16 port MEMBER port_)
  Q_PROPERTY(bool nonBlock MEMBER nonBlock_)

public:
  GNetClient(GObj *parent = nullptr) : GNet(parent) {}

  int family_{AF_UNSPEC};
  QString localIp_;
  quint16 localPort_{0};
  QString host_;
  quint16 port_{0};
  bool nonBlock_{true};
};
