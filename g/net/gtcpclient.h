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

#include "gip.h"
#include "gnetclient.h"
#include "gtcpsession.h"

// ----------------------------------------------------------------------------
// GTcpClient
// ----------------------------------------------------------------------------
struct GTcpClient : GNetClient {
  Q_OBJECT
  Q_PROPERTY(QString localIp MEMBER localIp_)
  Q_PROPERTY(quint16 localPort MEMBER localPort_)
  Q_PROPERTY(QString host MEMBER host_)
  Q_PROPERTY(quint16 port MEMBER port_)

public:
  GTcpClient(GObj *parent = nullptr);
  ~GTcpClient() override;

public:
  bool open() override;
  bool close() override;

public:
  GIp localIp_ {0};
  uint16_t localPort_ {0};
  QString host_;
  uint16_t port_ {0};
  GTcpSession* tcpSession_;
};
