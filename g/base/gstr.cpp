#include "gstr.h"

std::ostream& operator << (std::ostream& os, QString s) {
  os << s.toStdString();
  return os;
}
