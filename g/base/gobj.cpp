#include <QMetaObject>
#include <QMetaProperty>
#include "gobj.h"

GObj::~GObj() {
  if (err != nullptr) {
    delete err;
    err = nullptr;
  }
}

bool GObj::open() {
  SET_ERR(GStdErr(g::VIRTUAL_FUNCTION_CALL, "virtual function call"));
  return false;
}

bool GObj::close() {
  SET_ERR(GStdErr(g::VIRTUAL_FUNCTION_CALL, "virtual function call"));
  return false;
}

void GObj::helpCommandLine(std::ostream* os) {
  if (os == nullptr) os = &std::clog;
  const QMetaObject* mobj = metaObject();
  for (int i = 0; i < mobj->propertyCount(); i++) {
    QMetaProperty mpro = mobj->property(i);
    const char* name = mpro.name();
    QVariant value = property(name);
    *os << "-" << name << "=\"" << value.toString() << "\"" <<std::endl;
  }
}

bool GObj::parseCommandLine(int argc, const char* argv[], QString prefixName) {
  bool res = true;
  for (int i = 1; i < argc; i++) {
    QString line = argv[i];
    if (line.isEmpty())
      continue;
    if (line.at(0) != '-')
      continue;
    line = line.right(line.length() - 1);
    QStringList sl = line.split("=");
    if (sl.length() != 2)
      continue;
    QString name = sl.at(0);
    if (name.left(prefixName.length()) == prefixName)
      name = name.right(name.length() - prefixName.length());
    QString value = sl.at(1);
    if (!setProperty(qPrintable(name), value)) {
      SET_ERR(GStdErr(g::ERROR_IN_PARSING, QString("error in parsing name=%1 value=%2").arg(name, value)));
      res = false;
    }
  }
  return res;
}

// ----------------------------------------------------------------------------
// GTEST
// ----------------------------------------------------------------------------
#ifdef GTEST
#include <gtest/gtest.h>

#include <GTcpClient>
TEST(GObj, helpCommandLineTest) {
  GTcpClient tcpClient;
  tcpClient.helpCommandLine();
}

TEST(GObj, parseCommandLineTest) {
  GTcpClient tcpClient;
  const char* argv[] { "gtest", "-family=2", "-host=192.168.10.1", "-port=80", "-nonBlock=true" };
  tcpClient.parseCommandLine(5, argv);
  EXPECT_EQ(tcpClient.family_, AF_INET); // 2
  EXPECT_EQ(tcpClient.host_, "192.168.10.1");
  EXPECT_EQ(tcpClient.port_, "80");
  EXPECT_EQ(tcpClient.nonBlock_, true);
}

#endif // GTEST
