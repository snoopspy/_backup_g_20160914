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

#include "gnetserver.h"
#include "gsock.h"

// ----------------------------------------------------------------------------
// GTcpServer
// ----------------------------------------------------------------------------
struct GTcpServer : GNetServer {
  Q_OBJECT
  Q_PROPERTY(int backLog MEMBER backLog_)

public:
  GTcpServer(GObj* parent = nullptr);
  ~GTcpServer() override;

  bool open() override;
  bool close() override;

  bool listen();
  GSock accept(GSockAddr *sockAddr = nullptr, socklen_t *addrLen = nullptr);
  bool acceptClose();

  int backLog_{1024};

  GSock acceptSock_{-1};
};
