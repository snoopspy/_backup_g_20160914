#include <GStackTrace>

void foo1() { GStackTrace::instance().dump(); }
static void foo2() { foo1(); }
void foo3() { foo2(); }

int main() {
  foo3();
}
