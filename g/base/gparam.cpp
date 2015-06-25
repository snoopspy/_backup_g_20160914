#include <QMetaObject>
#include <QMetaProperty>
#include "gparam.h"

// ----------------------------------------------------------------------------
// GParam
// ----------------------------------------------------------------------------
GParam::GParam(int argc, char* argv[]) {
  for (int i = 0; i < argc; i++) {
    argv_.push_back(QString(argv[i]));
  }
}

GParam::~GParam() {
  if (argv_.size() != 1) {
    std::cerr << "Unknown parameter:" << std::endl;
    for (int i = 1; i < argv_.size(); i++)
      std::cerr << argv_[i] << std::endl;
  }
}

void GParam::help(GObj* obj) {
  const QMetaObject* mobj = obj->metaObject();
  for (int i = 0; i < mobj->propertyCount(); i++) {
    QMetaProperty mpro = mobj->property(i);
    const char* name = mpro.name();
    QVariant value = obj->property(name);
    std::cout << name << "=\"" << value.toString() << "\"" <<std::endl;
  }
}

void GParam::parse(GObj* obj) {
  if (argc_ == 2) {
    if (argv_[1] == "help" || argv_[1] == "ghelp") {
      help(obj);
    }
  }
  int i = 1;
  while (i < argc_) {
    QString line = argv_[i];
    QStringList sl = line.split("=");
    if (sl.length() != 2)
      continue;
    QString name = sl.at(0);
    QString value = sl.at(1);
    if (obj->setProperty(qPrintable(name), value)) {
      argc_--;
      argv_.removeAt(i);
    } else {
      i++;
    }
  }
}
