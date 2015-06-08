#include "gtcpserver.h"

// ----------------------------------------------------------------------------
// GTcpServer
// ----------------------------------------------------------------------------
GTcpServer::GTcpServer(GObj *parent) : GNetServer(parent) {

}

GTcpServer::~GTcpServer() {

}

bool GTcpServer::open() {
  // gilgil temp 2015.06.08
  err = new GStdErr(g::NOT_SUPPORTED, "NOT_SUPPORTED");
  return false;
}

bool GTcpServer::close() {
  // gilgil temp 2015.06.08
  err = new GStdErr(g::NOT_SUPPORTED, "NOT_SUPPORTED");
  return false;
}
