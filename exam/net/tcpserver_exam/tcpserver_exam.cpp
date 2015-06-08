#include <glog/logging.h>
#include <GTcpServer>

int main() {
  GTcpServer tcpServer;

  if (!tcpServer.open()) {
    LOG(ERROR) << tcpServer.err;
    return EXIT_FAILURE;
  }

  return 0;
}
