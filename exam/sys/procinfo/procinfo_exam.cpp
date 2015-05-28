#include <iostream>
#include <string.h>
#include <GProcInfo>

int main() {
  GProcInfo pi;
  int64_t oldRss = pi.load().rss();

  static int SIZE = 10 * 1024 * 1024; // 10M Bytes
  char* buf = (char*) malloc(SIZE);
  memset(buf, 0, SIZE);

  int64_t newRss = pi.load().rss();
  int64_t diffRss = newRss - oldRss;

  std::cout
    << "oldRss=" << oldRss
    << " newRss=" << newRss
    << " diffRss=" << diffRss
    << std::endl;
}
