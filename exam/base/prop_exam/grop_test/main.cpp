#include <QApplication>
#include <GPropEditor>

#include <QLineEdit>
#include "myobj.h"
#include "netclient.h"

QObject* createObject()
{
  QObject* res = new NetClient;
  //QObject* res = new QLineEdit;
  //QObject* res = new MyObj;

  res->setObjectName("myName");
  return res;
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QObject* object = createObject();
  GPropEditor editor;
  editor.setObject(object);
  editor.show();
  int res = a.exec();
  delete object;
  return res;
}
