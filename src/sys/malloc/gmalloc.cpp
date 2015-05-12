#include <dlfcn.h>
#include <malloc.h>
#include <stdio.h>
#include "gmalloc.h"

// ----------------------------------------------------------------------------
// GMallocImpl
// ----------------------------------------------------------------------------
class GMallocImpl {
public:
  bool inited_ = false;
  void* (*oldMalloc_)(size_t size) = nullptr;
  void (*oldFree_)(void* ptr) = nullptr;

public:
  GMallocImpl() {
    init();
  }

  virtual ~GMallocImpl() {
    fini();
  }

public:
  bool init() {
    if (inited_) return false;
    inited_ = true;
    oldMalloc_ = (void*(*)(size_t))dlsym(RTLD_NEXT, "malloc");
    if (oldMalloc_ == nullptr) {
      fprintf(stderr, "dlsym('malloc') return nullptr dlerror=%s\n", dlerror());
      oldFree_ = nullptr;
      return false;
    }
    oldFree_ = (void(*)(void*))dlsym(RTLD_NEXT, "free");
    if (oldFree_ == nullptr) {
      fprintf(stderr, "dlsym('malloc') return nullptr dlerror=%s\n", dlerror());
      return false;
    }
    return true;
  }

  bool fini() {
    if (!inited_) return false;
    inited_ = false;
    bool res = true;
    // ----- gilgil temp 2015.05.12 -----
    /*
    if (oldMalloc_ != nullptr) {
      int nRes = dlclose((void*)oldMalloc_);
      if (nRes != 0) {
        fprintf(stderr, "dlclose(oldMalloc_) return %d\n", nRes);
        res = false;
      }
      oldMalloc_ = nullptr;
    }
    if (oldFree_ != nullptr) {
      int nRes = dlclose((void*)oldFree_);
      if (nRes != 0) {
        fprintf(stderr, "dlclose(oldFree_) return %d\n", nRes);
        res = false;
      }
      oldFree_ = nullptr;
    }
    */
    oldMalloc_ = nullptr;
    oldFree_ = nullptr;
    // ----------------------------------
    return res;
  }

  static GMallocImpl& instance() {
    static GMallocImpl mallocImpl;
    return mallocImpl;
  }
};

// ----------------------------------------------------------------------------
// GMalloc
// ----------------------------------------------------------------------------
bool GMalloc::init() {
  GMallocImpl& mallocImpl = GMallocImpl::instance();
  return mallocImpl.init();
}

bool GMalloc::fini() {
  GMallocImpl& mallocImpl = GMallocImpl::instance();
  return mallocImpl.fini();
}

// ----------------------------------------------------------------------------
// override function
// ----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C"
{
#endif

void *malloc(size_t size) __THROW {
  GMallocImpl& mallocImpl = GMallocImpl::instance();
  void* p = mallocImpl.oldMalloc_(size);
  printf("malloc(%zu) return %p\n", size, p);
  return p;
}

void free(void* ptr) __THROW {
  GMallocImpl& mallocImpl = GMallocImpl::instance();
  mallocImpl.oldFree_(ptr);
  printf("free(%p)\n", ptr);
}

#ifdef __cplusplus
}
#endif
