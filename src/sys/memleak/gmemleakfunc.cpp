#ifdef _DEBUG

#include <stdio.h>  // printf
#include <stdlib.h> // malloc

#include "gmemleakfunc.h"
#include "gmemleakmgr.h"

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-value"
#endif // __GNUC__

#define _debug

// ----------------------------------------------------------------------------
// function for c
// ----------------------------------------------------------------------------
void* gmemleak_malloc(size_t size, const char* file, const int line) {
  void* res;

  _debug("gmemleak_malloc(%d, %s, %d)\n", (int)size, file, line);
  res = malloc(size);
  res = gmemleak_mgr_add(res, size, file, line);
  return res;
}

void* gmemleak_calloc(size_t nmemb, size_t size, const char* file, const int line) {
  void* res;

  _debug("gmemleak_calloc(%d, %d, %s, %d)\n", (int)nmemb, (int)size, file, line);
  res = calloc(nmemb, size);
  res = gmemleak_mgr_add(res, size, file, line);
  return res;
}

void* gmemleak_realloc(void *ptr, size_t size, const char* file, const int line) {
  void* res;

  _debug("gmemleak_realloc(%p, %d, %s, %d)\n", ptr, (int)size, file, line);
  res = realloc(ptr, size);
  if (res != ptr) {
    gmemleak_mgr_del(ptr);
    res = gmemleak_mgr_add(res, size, file, line);
  }
  return res;
}

void gmemleak_free(void *ptr, const char* file, const int line) {
  _debug("gmemleak_free(%p, %s, %d)\n", ptr, file, line);
  gmemleak_mgr_del(ptr);
  free(ptr);
}

// ----------------------------------------------------------------------------
// function for cpp
// ----------------------------------------------------------------------------
void* operator new(size_t size, const char* file, const int line) throw(std::bad_alloc) {
    _debug("new(%d, %s, %d)\n", (int)size, file, line);
    void* res = malloc(size);
    res = gmemleak_mgr_add(res, size, file, line);
    return res;
}

void* operator new[](size_t size, const char* file, const int line) throw(std::bad_alloc) {
    _debug("new[](%d, %s, %d)\n", (int)size, file, line);
    void* res = malloc(size);
    res = gmemleak_mgr_add(res, size, file, line);
    return res;
}

void operator delete(void* ptr) throw() {
    _debug("delete(%p)\n", ptr);
    gmemleak_mgr_del(ptr);
    free(ptr);
}

void operator delete[](void* ptr) throw() {
    _debug("delete[](%p)\n", ptr);
    gmemleak_mgr_del(ptr);
    free(ptr);
}

#endif // _DEBUG
