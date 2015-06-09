#include <QApplication>
#include <GPropEditor>

#include <QLineEdit>
#include "myobj.h"
#include "netclient.h"
#include <GTcpClient>
#include "g/net/gip.h"

QObject* createObject() {
  //QObject* res = new NetClient;
  //QObject* res = new QLineEdit;
  //QObject* res = new MyObj;
  GTcpClient* res = new GTcpClient;
  res->localIp_ = "1.2.3.4";

  GIp ip;
  res->setObjectName("myName");
  return res;
}

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QObject* object = createObject();
  GPropEditor editor;
  editor.setObject(object);
  editor.show();
  int res = a.exec();
  delete object;
  return res;
}
