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

// ----------------------------------------------------------------------------
// GTcpClient
// ----------------------------------------------------------------------------
struct GTcpClient : GNetClient {
  Q_OBJECT

  GIp localIp_ {0};
  uint16_t localPort_ {0};
  QString host_;
  uint16_t port_ {0};
};
