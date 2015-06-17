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

#include "g/base/event/geventsock.h"
#include "gtcpsession.h"

// ----------------------------------------------------------------------------
// GAsyncTcpSession
// ----------------------------------------------------------------------------
struct GAsyncTcpSession : GTcpSession {
  GAsyncTcpSession(GObj* parent) : GTcpSession(parent) {}
  ~GAsyncTcpSession() override;

  bool open() override;
  bool close() override;

  void assignEventBase(
    GEventBase* eventBase,
    event_callback_fn callback,
    void* arg = nullptr,
    GEvent::Options options = EV_READ | EV_PERSIST);

  GEventSock* eventSock_{nullptr};
};
