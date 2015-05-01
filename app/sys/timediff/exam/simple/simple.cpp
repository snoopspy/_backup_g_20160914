#include <chrono>
#include <thread>
#include <GTimeDiffChrono>

int main() {
  GTimeDiffChrono pfm(__LINE__);
  std::this_thread::sleep_for(std::chrono::seconds(1));
  pfm.check(__LINE__);
}

