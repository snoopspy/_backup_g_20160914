#include <cstdlib>

void foo(char* p, size_t size) __attribute__ ((noinline));

void foo(char* p, size_t size) {
  for (size_t i = 0; i < size; i++) p[i] = '\0';
}

int main() {
  char* p;
  p = new char[1]; // memory leak
  foo(p, 1); // disable code optimization
  p = new char[2];
  foo(p, 2); // disable code optimization
  delete[] p;
}
