#include <iostream>
#include <GErr>

using namespace std;

struct Obj {
  GErr& err() {

    return err_;
  }
private:
  GErr err_ { g::FAIL, "NOT_SUPPORTED in Obj class" };
};

int main() {
  {
    GErr err;
    clog << err << endl;
  }

  {
    GErr err{ g::NOT_SUPPORTED };
    clog << err << endl;
  }

  {
    GErr err { g::NOT_SUPPORTED, "NOT_SUPPORTED" };
    clog << err << endl;
  }

  {
    Obj obj;
    GErr err = obj.err();
    clog << err << endl;
  }
}
