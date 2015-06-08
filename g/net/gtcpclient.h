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

#include "gnetclient.h"
#include "gtcpsession.h"

// ----------------------------------------------------------------------------
// GTcpClient
// ----------------------------------------------------------------------------
struct GTcpClient : GNetClient {
  Q_OBJECT
  Q_PROPERTY(QString localIp MEMBER localIp)
  Q_PROPERTY(quint16 localPort MEMBER localPort)
  Q_PROPERTY(QString host MEMBER host)
  Q_PROPERTY(quint16 port MEMBER port)

public:
  GTcpClient(GObj *parent = nullptr);
  ~GTcpClient() override;

  bool open() override;
  bool close() override;

  QString localIp;
  quint16 localPort {0};
  QString host;
  quint16 port {0};
  GTcpSession* tcpSession;
};
