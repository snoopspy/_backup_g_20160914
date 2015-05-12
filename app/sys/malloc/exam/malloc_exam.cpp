#include <malloc.h>
#include <GMalloc>

int main() {
  //GMalloc::init();
  void* p;
  p = malloc(1); // memory leak
  p = malloc(2);
  free(p);
}
