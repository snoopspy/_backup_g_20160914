#include "log/glog.h"
#include "gpropitem_base.h"

#ifdef QT_GUI_LIB

// ----------------------------------------------------------------------------
// GPropItem_Base
// ----------------------------------------------------------------------------
void GPropItem_Base::myEditingFinished() {
  bool res = object->setProperty(mpro.name(), QVariant::fromValue<QString>(lineEdit->text()));
  if (!res) {
    LOG(ERROR) << QString("object->setProperty(%1, %2) return false").arg(mpro.name()).arg(lineEdit->text());
  }
  update();
}

#endif // QT_GUI_LIB
