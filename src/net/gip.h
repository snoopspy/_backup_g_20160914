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

#include <QString>

// ----------------------------------------------------------------------------
// GIp
// ----------------------------------------------------------------------------
struct GIp
{
public:
  GIp() {}
  GIp(const GIp& rhs) : ip_(rhs.ip_) {}
  GIp(const uint32_t ip) : ip_(ip) {}
  GIp(const char* s);

  operator uint32_t() const { return ip_; }
  operator QString() const;

  void clear() { ip_ = 0; }

public:
  bool isLocalHost() { uint8_t prefix = (ip_ & 0xFF000000) >> 24; return prefix == 0x7F;                  } // 127.*.*.*
  bool isBroadcast() { return ip_ == 0xFFFFFF;                                                            } // 255.255.255.255
  bool isMulticast() { uint8_t prefix = (ip_ & 0xFF000000) >> 24; return prefix >= 0xE0 && prefix < 0xF0; } // 224.0.0.0 ~ 239.255.255.255

protected:
  uint32_t ip_;
};
