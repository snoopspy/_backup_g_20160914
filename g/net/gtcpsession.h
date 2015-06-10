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
  GTcpSession(GObj *parent = nullptr) : GIOObj(parent) {}
  GTcpSession(GObj *parent, GSock sock) : GIOObj(parent) , sock_(sock) {}
  ~GTcpSession() override { close(); }

  bool open() override {
    return sock_ != -1;
  }

  bool close() override {
    if (!sock_.shutdown())
      return false;
    if (!sock_.close())
      return false;
    return true;
  }

  ssize_t read(char *buf, ssize_t len) override {
    return sock_.recv(buf, len);
  }

  ssize_t write(const char *buf, ssize_t len) override {
    return sock_.send(buf, len);
  }

  GSock sock_;
};
