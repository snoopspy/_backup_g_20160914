#include <iostream>
#include <GErr>

int main() {
  GErrCode errCode { g::OK };
  std::cout << errCode << std::endl;

  GErrMsg errMsg { g::FAIL, "FAIL" };
  std::cout << errMsg << std::endl;
}
