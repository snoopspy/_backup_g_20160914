#ifndef __NET_CLIENT_H__
#define __NET_CLIENT_H__

#include <QObject>
#include "ip.h"

class NetClient : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString host MEMBER host)
  Q_PROPERTY(QString ip MEMBER ip)

public:
  NetClient(QObject* parent = 0) : QObject(parent) {}
  virtual ~NetClient() {}

public:
  QString host;
  Ip ip;
};

#endif // __NET_CLIENT_H__
