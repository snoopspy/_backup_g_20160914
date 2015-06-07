#ifndef MYOBJ_H
#define MYOBJ_H

#include <QObject>

class MyObj : public QObject {
  Q_OBJECT
  Q_PROPERTY(QChar my_ch MEMBER my_ch)
  Q_PROPERTY(int my_quint8 MEMBER my_quint8)
public:
  explicit MyObj(QObject *parent = 0) : QObject(parent) {
    my_ch = 'a';
    my_quint8 = 8;
  }

  virtual ~MyObj() {}

public:
  QChar my_ch;
  quint8 my_quint8;
};

#endif // MYOBJ_H
