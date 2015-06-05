#ifndef __IP_H__
#define __IP_H__

//#include <QMetaType>
#include <QString>

class Ip
{
public:
  Ip() { value = 0; }

  Ip(const Ip& rhs) { value = rhs.value; }
  Ip(const quint32 rhs) { value = rhs; }
  Ip(const QString rhs) { value = rhs.toUInt(); }
  Ip(const char* rhs) { value = QString(rhs).toUInt(); }

  explicit operator quint32() { return value; }
  /*explicit*/ operator QString() { return QString::number(value); } // default operator
  explicit operator const char*() { return qPrintable(QString::number(value)); }

protected:
  quint32 value;
};
//Q_DECLARE_METATYPE(Ip)

#endif // __IP_H__
