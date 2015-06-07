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
#include <QTreeWidgetItem>

struct GPropItemParam {
  QTreeWidget* treeWidget;
  QObject* object;
  QMetaProperty mpro;
};

class GPropItem : public QObject, public QTreeWidgetItem {
  Q_OBJECT
public:
  GPropItem(GPropItemParam param) : QTreeWidgetItem(param.treeWidget) {
    object = param.object;
    mpro = param.mpro;
    setText(0, mpro.name());
  }

  virtual void update() = 0;

protected:
  QObject* object;
  QMetaProperty mpro;
};

#endif // QT_GUI_LIB
