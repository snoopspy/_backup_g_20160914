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
#include "gtcpsession.h"

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

  virtual GTcpSession* accept();

  int backLog_{1024};

  GTcpSession* acceptSession_;
};
