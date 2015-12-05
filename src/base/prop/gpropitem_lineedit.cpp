#include "gpropitem_lineedit.h"

#ifdef QT_GUI_LIB

// ----------------------------------------------------------------------------
// GPropItemLineEdit
// ----------------------------------------------------------------------------
void GPropItemLineEdit::init(GPropItemParam param) {
  GPropItem::init(param);
  lineEdit_ = new QLineEdit(param.treeWidget_);
  lineEdit_->setFrame(false);
  param.treeWidget_->setItemWidget(item_, 1, lineEdit_);
}

#endif // QT_GUI_LIB
