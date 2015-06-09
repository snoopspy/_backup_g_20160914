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
  GTcpServer(GObj *parent = nullptr);
  ~GTcpServer() override;

  bool open() override;
  bool close() override;

  QList<GTcpSession*> tcpSession_;
};
