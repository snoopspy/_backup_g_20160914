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
    UNKNOWN = 1
  };
}

// ----------------------------------------------------------------------------
// GErr
// ----------------------------------------------------------------------------
struct GErr {
  virtual int code() = 0;
  virtual char* msg() = 0;
};
std::ostream& operator << (std::ostream& os, GErr& err);

// ----------------------------------------------------------------------------
// GErrCode
// ----------------------------------------------------------------------------
struct GErrCode : GErr {
  GErrCode(int code) : code_(code) {}
  int code() override { return code_; }
  char* msg() override;

protected:
  int code_;
};

// ----------------------------------------------------------------------------
// GErrMsg
// ----------------------------------------------------------------------------
struct GErrMsg : GErrCode {
  GErrMsg(int code, char* msg) : GErrCode(code), msg_(msg) {}
  int code() override { return code_; }
  char* msg() override { return (char*)msg_.c_str(); }

protected:
  std::string msg_;
};
