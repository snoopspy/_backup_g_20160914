#include "ip.h"

#ifdef GTEST
#include <gtest/gtest.h>

TEST(Ip, defaultTest)
{
  {
    Ip ip;
  }
  {
    Ip ip(1234);
  }
  {
    Ip ip("1234");
  }
}

TEST(Ip, convTest)
{
  {
    Ip ip(1234);
  }
  {
    Ip ip("1234");
  }
}

TEST(Ip, assignTest)
{
  {
    Ip ip;
    ip = 1234;
  }
  {
    Ip ip;
    ip = "1234";
  }
}

TEST(Ip, revAssignTest)
{
  {
    quint32 i;
    Ip ip = 1234;
    i = (quint32)ip;
    (void)i;
  }
  {
    QString s;
    Ip ip = "1234";
    s = ip;
  }
}

#endif // GTEST
