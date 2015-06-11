#include "gobj.h"

GObj::~GObj() {
  if (err != nullptr) {
    delete err;
    err = nullptr;
  }
}

bool GObj::open() {
  SET_ERR(err, new GStdErr(g::VIRTUAL_FUNCTION_CALL, "virtual function call"));
  return false;
}

bool GObj::close() {
  SET_ERR(err, new GStdErr(g::VIRTUAL_FUNCTION_CALL, "virtual function call"));
  return false;
}
