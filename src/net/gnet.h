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

#include "gsock.h"
#include "gsockaddr.h"
#include "base/gerr.h"

// ----------------------------------------------------------------------------
// GNet
// ----------------------------------------------------------------------------
class GNet {
public:
  static int bind(GSock sock, GSockAddr& sockAddr, socklen_t len = sizeof(struct sockaddr));
};
