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

#include "gpropitem_base.h"

// ----------------------------------------------------------------------------
// GPropItem_QChar
// ----------------------------------------------------------------------------
class GPropItem_QChar : public GPropItem_Base
{
  Q_OBJECT
public:
  GPropItem_QChar(GPropItemParam param) : GPropItem_Base(param)
  {
  }

protected slots:
  void myEditingFinished() override
  {
    QChar value;
    QString text = lineEdit->text();
    if (text.length() == 0) value = '\0';
    else value = text.at(0);
    object->setProperty(mpro.name(), value);
    update();
  }
};

// ----------------------------------------------------------------------------
// GPropItemCreator_QChar
// ----------------------------------------------------------------------------
class GPropItemCreator_QChar : public GPropItemCreator
{
public:
  GPropItem* createItem(GPropItemParam param) override
  {
    if (param.mpro.userType() != QMetaType::QChar) return nullptr;
    return new GPropItem_QChar(param);
  }
};

#endif // QT_GUI_LIB
