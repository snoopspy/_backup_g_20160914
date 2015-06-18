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

#include "gtcpclient.h"
#include "gasynctcpsession.h"

// ----------------------------------------------------------------------------
// GAsyncTcpClient
// ----------------------------------------------------------------------------
struct GAsyncTcpClient : GTcpClient {
  GAsyncTcpClient(GObj* parent = nullptr);
};
