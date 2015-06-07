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

#include <QCheckBox>
#include "gpropitemcreator.h"

// ----------------------------------------------------------------------------
// GPropItem_Bool
// ----------------------------------------------------------------------------
class GPropItem_Bool : public GPropItem {
  Q_OBJECT

public:
  GPropItem_Bool(GPropItemParam param) : GPropItem(param) {
    checkBox = new QCheckBox(param.treeWidget);
    QObject::connect(checkBox, SIGNAL(clicked(bool)), this, SLOT(myClicked(bool)));
    param.treeWidget->setItemWidget(this, 1, checkBox);
  }

  void update() override {
    checkBox->setChecked(object->property(mpro.name()).toBool());
  }

protected:
  QCheckBox* checkBox;

protected slots:
  void myClicked(bool checked) {
    object->setProperty(mpro.name(), checked);
    update();
  }
};

// ----------------------------------------------------------------------------
// GPropItemCreator_Bool
// ----------------------------------------------------------------------------
class GPropItemCreator_Bool : public GPropItemCreator {
public:
  GPropItem* createItem(GPropItemParam param) override {
    if (param.mpro.userType() != QMetaType::Bool) return nullptr;
    return new GPropItem_Bool(param);
  }
};

#endif // QT_GUI_LIB
