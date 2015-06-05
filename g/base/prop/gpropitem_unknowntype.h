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
// GPropItem_UnknownType
// ----------------------------------------------------------------------------
class GPropItem_UnknownType : public GPropItem
{
  Q_OBJECT

public:
  GPropItem_UnknownType(GPropItemParam param) : GPropItem(param)
  {
    this->setBackground(1, QBrush(Qt::lightGray));
  }

  void update() override
  {
  }
};

// ----------------------------------------------------------------------------
// GPropItemCreator_UnknownType
// ----------------------------------------------------------------------------
class GPropItemCreator_UnknownType : public GPropItemCreator
{
public:
  GPropItem* createItem(GPropItemParam param) override
  {
    return new GPropItem_UnknownType(param);
  }
};

#endif // QT_GUI_LIB
