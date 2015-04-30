// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.1
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_MEM_LEAK_MGR_H__
#define __V_MEM_LEAK_MGR_H__

#include <stddef.h> // size_t

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------------
// export function
// ----------------------------------------------------------------------------
void gmemleak_mgr_start(void);
void gmemleak_mgr_stop(void);

// ----------------------------------------------------------------------------
// used internally
// ----------------------------------------------------------------------------
void* gmemleak_mgr_add(void* ptr, size_t size, const char* file, const int line);
void  gmemleak_mgr_del(void* ptr);

#ifdef __cplusplus
}
#endif

#endif // __V_MEM_LEAK_MGR_H__
