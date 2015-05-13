#include <dlfcn.h>
#include <stdio.h>

// ----------------------------------------------------------------------------
// GMalloc
// ----------------------------------------------------------------------------
class GMalloc {
public:
  bool inited_ = false;
  void* (*oldMalloc_)(size_t size) = nullptr;
  void (*oldFree_)(void* ptr) = nullptr;

public:
  GMalloc() {
    init();
  }

  virtual ~GMalloc() {
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
    return true;
  }

  void* acquire(size_t size) {
    if (!inited_) return nullptr;
    void* ptr = GMalloc::instance().oldMalloc_(size);
    printf("GMalloc::acquire(%p) %zu\n", ptr, size);
    return ptr;
  }

  void release(void* ptr) {
    if (!inited_) return;
    printf("GMalloc::release(%p)\n", ptr);
  }

  static GMalloc& instance() {
    static GMalloc _instance;
    return _instance;
  }
};

// ----------------------------------------------------------------------------
// override function
// ----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C"
{
#endif

void *malloc(size_t size) __THROW {
  return GMalloc::instance().acquire(size);
}

void free(void* ptr) __THROW {
  GMalloc::instance().release(ptr);
}

#ifdef __cplusplus
}
#endif
