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

#include "g/base/gioobj.h"
#include "gsock.h"

// ----------------------------------------------------------------------------
// GTcpSession
// ----------------------------------------------------------------------------
struct GTcpSession : GIOObj {
  GTcpSession() : GIOObj(nullptr) {}
  GTcpSession(GSock sock) : GIOObj(nullptr), sock_(sock) {}
  ~GTcpSession() override { close(); }

  bool open() override {
    return sock_ != -1;
  }

  bool close() override {
    bool res = true;
    if (!sock_.shutdown())
      res = false;
    if (!sock_.close())
      res = false;
    sock_ = -1;
    return res;
  }

  ssize_t read(char *buf, ssize_t len) override {
    return sock_.recv(buf, len);
  }

  ssize_t write(const char *buf, ssize_t len) override {
    return sock_.send(buf, len);
  }

  GSock sock_{-1};
};
