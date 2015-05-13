#include <cstdlib>

void foo(char* p, size_t size) __attribute__ ((noinline));

void foo(char* p, size_t size) {
  for (size_t i = 0; i < size; i++) p[i] = '\0';
}

int main() {
  char* p = (char*)malloc(1);
  foo(p, 1); // disable code optimization
  free(p);
}
