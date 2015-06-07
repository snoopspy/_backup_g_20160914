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

#include <QMetaProperty>
#include "gpropeditor.h"
#include "gpropitem.h"

// ----------------------------------------------------------------------------
// GPropItemCreator
// ----------------------------------------------------------------------------
class GPropItemCreator {
public:
  virtual GPropItem* createItem(GPropItemParam param) = 0;
};

#endif // QT_GUI_LIB
