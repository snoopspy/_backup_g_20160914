#include <GMemLeak>

void first_test()
{
  delete new int;
  delete[] new int[256];
}

#include <GMemLeakCancel>
void cancel_test()
{
  delete new int;
  delete[] new int[256];
}

#include <GMemLeak>
void second_test()
{
  delete new int;
  delete[] new int[256];
}

int main()
{
  first_test();
  cancel_test();
  second_test();
  return 0;
}
