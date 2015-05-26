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
    UNKNOWN = 1,
    NOT_SUPPORTED
  };
}

// ----------------------------------------------------------------------------
// GErr
// ----------------------------------------------------------------------------
struct GErr {
  GErr() : code_(g::OK) {}
  GErr(int code) : code_(code) {}
  GErr(int code, std::string msg) : code_(code), msg_(msg) {}

  int code() { return code_; }
  std::string msg();

protected:
  int code_;
  std::string msg_;
};
std::ostream& operator << (std::ostream& os, GErr& err);
