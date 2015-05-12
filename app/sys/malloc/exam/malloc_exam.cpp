#include <map>
//#include <malloc.h>
#include <GMalloc>

class Obj {
public:
  char buf[256];
};

int main() {
  GMalloc::init();
  void* p;
  p = malloc(1); // memory leak
  p = malloc(2);
  free(p);
  std::map<int, Obj> objList;
  objList[0] = Obj();
  objList[1] = Obj();
}
