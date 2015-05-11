#include <dlfcn.h>
#include <stdio.h>
#include "gmalloc.h"

// ----------------------------------------------------------------------------
// GMallocImpl
// ----------------------------------------------------------------------------
class GMallocImpl {
public:
  static void* (*oldMalloc)(size_t) = nullptr;
  static void (*oldFree)(void*) = nullptr;
  static bool active = false;

public:
  static bool init();
  static bool fini();
};






static void mtrace_init(void)
{
    real_malloc = dlsym(RTLD_NEXT, "malloc");
    if (NULL == real_malloc) {
        fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
    }
}

void *malloc(size_t size)
{
    if(real_malloc==NULL) {
        mtrace_init();
    }

    void *p = NULL;
    fprintf(stderr, "malloc(%d) = ", size);
    p = real_malloc(size);
    fprintf(stderr, "%p\n", p);
    return p;
}

int main() {
  mtrace_init();
}
