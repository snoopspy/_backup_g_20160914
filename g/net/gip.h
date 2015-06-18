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
struct GIp final {
public:
  GIp() {}
  GIp(const GIp& rhs) : ip_(rhs.ip_) {}
  GIp(const quint32 ui) : ip_(ui) {}
  GIp(const char* p) { operator =(p); }
  GIp(const QString s) { operator =(s); }

  GIp& operator =(const GIp& rhs) { ip_ = rhs.ip_; return *this; }
  GIp& operator =(const quint32 ui) { ip_ = ui; return *this; }
  GIp& operator =(const char* p);
  GIp& operator =(const QString s) { *this = qPrintable(s); return *this; }

  /*explicit*/ operator quint32() const { return ip_; } // default operator
  explicit operator const char*() const { return qPrintable((QString)*this); }
  explicit operator QString() const;

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
