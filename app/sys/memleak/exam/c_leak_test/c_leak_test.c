#include <stdlib.h>
#include <GMemLeak>
#include <GMemLeakMgr>

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-result"
#endif // __GNUC__

void malloc_test()
{
  gmemleak_mgr_start();
  malloc(256);
  gmemleak_mgr_stop();
}

void calloc_test()
{
  gmemleak_mgr_start();
  calloc(4, 256);
  gmemleak_mgr_stop();
}

void realloc_test()
{
  void *p;

  gmemleak_mgr_start();
  p = malloc(4);
  realloc(p, 4);
  gmemleak_mgr_stop();

  gmemleak_mgr_start();
  p = malloc(4);
  realloc(p, 400000);
  gmemleak_mgr_stop();
}

int main()
{
  malloc_test();
  calloc_test();
  realloc_test();
  return 0;
}
