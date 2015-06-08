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

#include "gnet.h"

// ----------------------------------------------------------------------------
// GNetClient
// ----------------------------------------------------------------------------
struct GNetClient : GNet {
  Q_OBJECT
  Q_PROPERTY(bool ip6 MEMBER ip6_)
  Q_PROPERTY(bool ip6Only MEMBER ip6Only_)

public:
  GNetClient(GObj *parent = nullptr) : GNet(parent) {}

public:
  bool ip6_{false};
  bool ip6Only_{false};
};
