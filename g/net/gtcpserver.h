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
  Q_PROPERTY(int backLog MEMBER backLog_)

public:
  GTcpServer(GObj *parent = nullptr);
  ~GTcpServer() override;

  bool open() override;
  bool close() override;

  bool bind();
  bool listen();
  GSock accept(GSockAddr *sockAddr = nullptr, socklen_t *addrLen = nullptr);
  bool acceptClose();

  int backLog_{1024};
  GSock acceptSock_{0};
  QList<GTcpSession*> tcpSessions_;
};
