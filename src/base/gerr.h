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
std::ostream& operator << (std::ostream& os, GErr& err);

// ----------------------------------------------------------------------------
// GLastErr
// ----------------------------------------------------------------------------
struct GLastErr : public GErr {
  GLastErr() { code_ = errno; }
  const char* name() override { return "errno"; }
  virtual std::string msg() override { return strerror(code_); }
};

// ----- gilgil temp 2015.06.04 -----
/*
// ----------------------------------------------------------------------------
// GErr
// ----------------------------------------------------------------------------
struct GErr {
  GErr() : code_(g::OK) {}
  GErr(int code) : code_(code) {}
  GErr(int code, std::string msg) : code_(code), msg_(msg) {}

  int code() { return code_; }
  std::string msg();
  void set(int code) { code_ = code; }
  void set(int code, std::string msg) { code_ = code; msg_ = msg; }

  void clear() { code_ = g::OK; msg_ = ""; }
  bool ok() { return code_ == g::OK; }

protected:
  int code_;
  std::string msg_;
};


extern thread_local GErr lastErr;
*/
// ----------------------------------
