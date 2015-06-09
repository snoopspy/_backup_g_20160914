#include <glog/logging.h>
#include <GTcpClient>

int main() {
  GTcpClient tcpClient;
  tcpClient.host_ = "127.0.0.1";
  tcpClient.port_ = 10065;

  if (!tcpClient.open()) {
    LOG(ERROR) << tcpClient.err;
    return EXIT_FAILURE;
  }

  return 0;
}
