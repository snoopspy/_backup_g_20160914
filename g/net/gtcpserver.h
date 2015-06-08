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

#include <QList>
#include "gnetserver.h"
#include "gtcpsession.h"

// ----------------------------------------------------------------------------
// GTcpServer
// ----------------------------------------------------------------------------
struct GTcpServer : GNetServer {
  Q_OBJECT
  Q_PROPERTY(QString localIp MEMBER localIp)
  Q_PROPERTY(quint16 port MEMBER port)

public:
  GTcpServer(GObj *parent = nullptr);
  ~GTcpServer() override;

  bool open() override;
  bool close() override;

  QString localIp;
  quint16 port{0};
  QList<GTcpSession*> tcpSession;
};
