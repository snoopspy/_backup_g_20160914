#include "gaddrinfo.h"
#include "gnet.h"

// ----------------------------------------------------------------------------
// GAddrInfo
// ----------------------------------------------------------------------------
GErr* GAddrInfo::query(QString host, QString port) {
  const char* pHost = nullptr;
  QByteArray baHost;
  if (!host.isEmpty()) {
    baHost = host.toLocal8Bit();
    pHost = baHost.constData();
  }

  const char* pPort = nullptr;
  QByteArray baPort;
  if (!port.isEmpty()) {
    baPort = port.toLocal8Bit();
    pPort = baPort.constData();
  }

  int res = getaddrinfo(pHost, pPort, &hints_, &infos_);
  if (res != 0) {
    return new GNetErr(res, gai_strerror(res));
  }
  return nullptr;
}
