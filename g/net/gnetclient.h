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
  Q_PROPERTY(QString localIp MEMBER localIp_)
  Q_PROPERTY(QString localPort MEMBER localPort_)
  Q_PROPERTY(QString host MEMBER host_)
  Q_PROPERTY(QString port MEMBER port_)

public:
  GNetClient(GObj* parent = nullptr) : GNet(parent) {}

  bool checkHostAndPort();
  GSock bind();
  bool connect(GSock sock);

  QString localIp_;
  QString localPort_{"0"};
  QString host_;
  QString port_{"0"};
};
