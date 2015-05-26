#include <iostream>
#include <GErr>

using namespace std;

struct Obj {
  GErr& err() {

    return err_;
  }
private:
  GErr err_ { g::FAIL, "FAIL in Obj class" };
};

int main() {
  {
    GErr err;
    clog << err << endl;
  }

  {
    GErr err{ g::FAIL };
    clog << err << endl;
  }

  {
    GErr err { g::FAIL, "FAIL" };
    clog << err << endl;
  }

  {
    Obj obj;
    GErr err = obj.err();
    clog << err << endl;
  }
}
