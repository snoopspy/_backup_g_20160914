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

#include <cstddef> // for size_t

// ----------------------------------------------------------------------------
// GMalloc
// ----------------------------------------------------------------------------
class GMalloc {
public:
  static bool init();
  static bool fini();
};

// ----------------------------------------------------------------------------
// override function
// ----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C"
{
#endif

void *malloc(size_t size) __THROW;
void free(void* ptr) __THROW;

#ifdef __cplusplus
}
#endif
