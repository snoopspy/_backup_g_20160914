// ----------------------------------------------------------------------------
//
// G Library
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifdef _DEBUG

// ----------------------------------------------------------------------------
// macro for c
// ----------------------------------------------------------------------------
#include "gmemleakfunc.h"

#undef  malloc
#define malloc(SIZE)        gmemleak_malloc ((SIZE),          __FILE__, __LINE__)
#undef  calloc
#define calloc(NMEMB, SIZE) gmemleak_calloc ((NMEMB), (SIZE), __FILE__, __LINE__)
#undef  realloc
#define realloc(PTR, SIZE)  gmemleak_realloc((PTR), (SIZE),   __FILE__, __LINE__)
#undef  free
#define free(PTR)           gmemleak_free   ((PTR),           __FILE__, __LINE__)

// ----------------------------------------------------------------------------
// macro for cpp
// ----------------------------------------------------------------------------
#ifdef __cplusplus

#undef  gmemleak_new
#define gmemleak_new new(__FILE__, __LINE__)
#undef  new
#define new gmemleak_new

#endif // __cplusplus

#endif // _DEBUG
