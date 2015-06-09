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

// #include <string.h> // gilgil temp 2015.06.09
#include <ostream>
#include <QString>

namespace g {
  enum {
    OK = 0,
    FAIL = -1,
    UNKNOWN = 1024,
    NOT_SUPPORTED,
    VIRTUAL_FUNCTION_CALL
  };

  enum {
    NET_CATEGORY = 1000
  };
}

// ----------------------------------------------------------------------------
// GErr
// ----------------------------------------------------------------------------
struct GErr {
  virtual ~GErr() {}

  virtual const char* name() = 0;
  virtual int code() = 0;
  virtual QString msg() = 0;
};

std::ostream& operator << (std::ostream& os, GErr& err);
std::ostream& operator << (std::ostream& os, GErr&& err);
std::ostream& operator << (std::ostream& os, GErr* err);

// ----------------------------------------------------------------------------
// GLastErr
// ----------------------------------------------------------------------------
struct GLastErr : GErr {
  GLastErr()                  { code_ = errno; }

  const char* name() override { return "LastErr"; }
  int code()         override { return code_; }
  QString msg()  override { return strerror(code_); }

  void setCode(int code)      { code_ = code; }

protected:
  int code_;
};

// ----------------------------------------------------------------------------
// GStdErr
// ----------------------------------------------------------------------------
struct GStdErr : GErr {
  GStdErr()                      { code_ = g::OK; }
  GStdErr(int code)              { code_ = code; }
  GStdErr(int code, QString msg) { code_ = code; msg_ = msg; }

  const char* name() override    { return "StdErr"; }
  int code()         override    { return code_; }
  QString msg()  override        { return msg_; }

  void setCode(int code)         { code_ = code; }
  void setMsg(QString msg)       { msg_ = msg; }

protected:
  int code_;
  QString msg_;
};
