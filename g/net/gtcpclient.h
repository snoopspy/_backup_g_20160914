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
  GTcpClient(GObj *parent = nullptr);
  ~GTcpClient() override;

  bool open() override;
  bool close() override;

  GTcpSession* tcpSession_;
};
