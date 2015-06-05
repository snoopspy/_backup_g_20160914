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

#include <QList>
#include "gpropitemcreator.h"

// ----------------------------------------------------------------------------
// GPropItemFactory
// ----------------------------------------------------------------------------
class GPropItemFactory : public QList<GPropItemCreator*>
{
public:
  GPropItem* createItem(GPropItemParam param);
  static GPropItemFactory& instance();
};

#endif // QT_GUI_LIB
