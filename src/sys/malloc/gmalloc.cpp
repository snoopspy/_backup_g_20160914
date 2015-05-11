#include <dlfcn.h>
#include <glog/logging.h>
#include "gmalloc.h"

// ----------------------------------------------------------------------------
// GMallocImpl
// ----------------------------------------------------------------------------
class GMallocImpl {
private:
  void* (*oldMalloc_)(size_t) = nullptr;
  void (*oldFree_)(void*) = nullptr;
   bool active = false;

public:
  bool init() {
    oldMalloc_ = (void*(*)(size_t))dlsym(RTLD_NEXT, "malloc");
    if (oldMalloc_ == nullptr) {
      LOG(ERROR) << "dlsym('malloc') return nullptr dlerror=" << dlerror();
      goto _error;
    }
    oldFree_ = (void(*)(void*))dlsym(RTLD_NEXT, "free");
    if (oldFree_ == nullptr) {
      LOG(ERROR) << "dlsym('malloc') return nullptr dlerror=" << dlerror();
      goto _error;
    }
    return true;
  _error:
    oldMalloc_ = nullptr;
    oldFree_ = nullptr;
    return false;
  }

  bool fini() {
    return true; // gilgil temp 2015.05.12
  }

public:
  static GMallocImpl& instance() {
    static GMallocImpl gMallocImpl;
    return gMallocImpl;
  }
};

// ----------------------------------------------------------------------------
// GMalloc
// ----------------------------------------------------------------------------
bool GMalloc::init() {
  GMallocImpl::instance().init();
}

bool GMalloc::fini() {
  GMallocImpl::instance().fini();
}
