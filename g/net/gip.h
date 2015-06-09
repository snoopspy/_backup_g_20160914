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
struct GIp {
public:
  GIp() {}
  GIp(const GIp& rhs) : ip_(rhs.ip_) {}
  GIp(const quint32 ip) : ip_(ip) {}
  GIp(const QString s);

  GIp& operator = (const GIp& rhs) { ip_ = rhs.ip_; return *this; }
  GIp& operator = (const quint32 ip) { ip_ = ip; return *this;}
  GIp& operator = (const QString s);

  operator quint32() const { return ip_; }
  operator QString() const;

  void clear() { ip_ = 0; }

public:
  bool isLocalHost() { // 127.*.*.*
    quint8 prefix = (ip_ & 0xFF000000) >> 24;
    return prefix == 0x7F;
  }

  bool isBroadcast() { // 255.255.255.255
    return ip_ == 0xFFFFFFFF;
  }

  bool isMulticast() { // 224.0.0.0 ~ 239.255.255.255
    quint8 prefix = (ip_ & 0xFF000000) >> 24;
    return prefix >= 0xE0 && prefix < 0xF0;
  }

protected:
  quint32 ip_;
};
