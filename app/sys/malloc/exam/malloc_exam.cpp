#include <malloc.h>
#include <GMalloc>

int main() {
  GMalloc::init();
  void* p;
  p = malloc(128); // memory leak
  p = malloc(256);
  free(p);
}
