#include <iostream>
#include <GErr>

using namespace std;

struct Obj {
  GErr& err() {

    return err_;
  }
private:
  GErrMsg err_ { ::g::NOT_SUPPORTED, "NOT_SUPPORTED" };
};

int main() {
  {
    GErr err;
    clog << err << endl;
  }

  {
    GErrCode errCode { g::OK };
    clog << errCode << endl;
  }

  {
    GErrMsg errMsg { g::FAIL, "FAIL" };
    clog << errMsg << endl;
  }

  {
    Obj obj;
    GErr err = obj.err();
    clog << err << endl;
  }
}
