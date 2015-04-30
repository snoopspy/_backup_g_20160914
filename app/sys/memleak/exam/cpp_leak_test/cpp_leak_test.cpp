#include <GMemLeak>
#include <GMemLeakMgr>

void new_test()
{
  gmemleak_mgr_start();
  new int;
  gmemleak_mgr_stop();
}

void new_arr_test()
{
  gmemleak_mgr_start();
  new int[256];
  gmemleak_mgr_stop();
}

int main()
{
  new_test();
  new_arr_test();
  return 0;
}
