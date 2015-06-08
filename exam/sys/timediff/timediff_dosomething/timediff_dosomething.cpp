#include <chrono>
#include <thread>
#include <GTimeDiffChrono>

void doSomething(int msec) {
  std::this_thread::sleep_for(std::chrono::milliseconds(msec));
}

int main() {
  GTimeDiffChrono td;
  for (int i = 0; i < 10; i++) {
    td.check(__LINE__);
    doSomething(10);
    td.check(__LINE__);
    doSomething(20);
    td.check(__LINE__);
    doSomething(30);
    td.check(__LINE__);
    doSomething(40);
  }
  td.report();
}
