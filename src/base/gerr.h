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

#include <cstring>
#include <ostream>
#include <string>

namespace g {
  enum {
    OK = 0,
    FAIL = -1,
    UNKNOWN = 1024,
    NOT_SUPPORTED
  };
}

// ----------------------------------------------------------------------------
// GErr
// ----------------------------------------------------------------------------
struct GErr {
  int code() { return code_; }
  void setCode(int code) { code_ = code; }

  virtual const char* name() = 0;
  virtual std::string msg() = 0;

protected:
  int code_;
};

std::ostream& operator << (std::ostream& os, GErr& err) {
  os << err.name() << ":" << (err.msg().empty() ? "no msg" : err.msg()) << " code=" << err.code();
  return os;
}

std::ostream& operator << (std::ostream& os, GErr* err) {
  if (err == nullptr) {
    os << "err is null";
    return os;
  }
  return operator << (os, *err);
}

// ----------------------------------------------------------------------------
// GLastErr
// ----------------------------------------------------------------------------
struct GLastErr : GErr {
  GLastErr() { code_ = errno; }

  const char* name() override { return "LastErr"; }
  std::string msg() override { return strerror(code_); }
};

// ----------------------------------------------------------------------------
// GStdErr
// ----------------------------------------------------------------------------
struct GStdErr : GErr {
  GStdErr() { code_ = g::OK; }
  GStdErr(int code) { code_ = code; }
  GStdErr(int code, std::string msg) { code_ = code; msg_ = msg; }

  const char* name() override { return "StdErr"; }
  std::string msg() override { return msg_; }

protected:
  std::string msg_;
};
