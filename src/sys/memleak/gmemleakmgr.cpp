#ifndef _DEBUG
extern "C" void gmemleak_mgr_start(void) {}
extern "C" void gmemleak_mgr_stop(void) {}
#endif // _DEBUG

#ifdef _DEBUG

#include <map>
#include <stdio.h>  // fprintf
#include "gmemleakmgr.h"

typedef struct {
  size_t size;
  char* file;
  int line;
} gmemleak_mgr_item_t;

typedef std::map<void*, gmemleak_mgr_item_t> gmemleak_mgr_t;

static gmemleak_mgr_t _gmemleak_mgr;

extern "C" void gmemleak_mgr_start(void) {
  _gmemleak_mgr.clear();
}

extern "C" void gmemleak_mgr_stop(void) {
  if (_gmemleak_mgr.size() <= 0) return;
  fprintf(stderr, "******************************************************************************\n");
  for (gmemleak_mgr_t::iterator it = _gmemleak_mgr.begin(); it != _gmemleak_mgr.end(); it++) {
    void* ptr = it->first;
    gmemleak_mgr_item_t& item = it->second;
    fprintf(stderr, "memory leak %p(%d bytes) %s:%d\n", ptr, (int)item.size, item.file, item.line);
  }
  fprintf(stderr, "******************************************************************************\n");
}

extern "C" void* gmemleak_mgr_add(void* ptr, size_t size, const char* file, const int line) {
  gmemleak_mgr_t::iterator it = _gmemleak_mgr.find(ptr);
  if (it != _gmemleak_mgr.end()) {
    fprintf(stderr, "ptr(%p) is already added size=%d file=%s line=%d\n", ptr, (int)size, file, line);
    return NULL;
  }
  gmemleak_mgr_item_t item;
  item.size = size;
  item.file = (char*)file;
  item.line = line;
  _gmemleak_mgr[ptr] = item;
  return ptr;
}

extern "C" void gmemleak_mgr_del(void* ptr) {
  if (ptr == NULL) {
    fprintf(stderr, "ptr is null\n");
    return;
  }
  gmemleak_mgr_t::iterator it = _gmemleak_mgr.find(ptr);
  if (it == _gmemleak_mgr.end()) return;
  _gmemleak_mgr.erase(it);
}

#endif // _DEBUG
