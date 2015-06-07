// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.1
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#pragma once

#ifdef QT_GUI_LIB

#include <QDebug> // gilgil temp 2015.03.24
#include <QLineEdit>
#include "gpropitemcreator.h"

// ----------------------------------------------------------------------------
// GPropItem_Base
// ----------------------------------------------------------------------------
class GPropItem_Base : public GPropItem {
  Q_OBJECT

public:
  GPropItem_Base(GPropItemParam param) : GPropItem(param) {
    lineEdit = new QLineEdit(param.treeWidget);
    lineEdit->setFrame(false);
    QObject::connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(myEditingFinished()));
    param.treeWidget->setItemWidget(this, 1, lineEdit);
  }

  void update() override {
    lineEdit->setText(object->property(mpro.name()).toString());
  }

protected:
  QLineEdit* lineEdit;

protected slots:
  virtual void myEditingFinished();
};

// ----------------------------------------------------------------------------
// GPropItemCreator_Base
// ----------------------------------------------------------------------------
class GPropItemCreator_Base : public GPropItemCreator {
public:
  GPropItemCreator_Base(int userType) {
    this->userType = userType;
  }

  GPropItem* createItem(GPropItemParam param) override {
    if (param.mpro.userType() != userType) return nullptr;
    return new GPropItem_Base(param);
  }

protected:
  int userType;
};

#endif // QT_GUI_LIB
