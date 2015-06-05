// ----------------------------------------------------------------------------
//
// G Library
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#pragma once

#ifdef QT_GUI_LIB

#include <QTreeWidget>

// ----------------------------------------------------------------------------
// GPropEditor
// ----------------------------------------------------------------------------
class GPropEditor : public QTreeWidget
{
  Q_OBJECT
  Q_PROPERTY(QObject* object READ object WRITE setObject)

public:
  explicit GPropEditor(QWidget *parent = 0);
  virtual ~GPropEditor();

public:
  QObject* object();
  void setObject(QObject* object);

protected:
  QObject* object_;
};

#endif // QT_GUI_LIB
