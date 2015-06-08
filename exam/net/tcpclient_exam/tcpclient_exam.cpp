#include <glog/logging.h>
#include <GTcpClient>

int main() {
  GTcpClient tcpClient;
  tcpClient.host = "127.0.0.1";
  tcpClient.port = 10065;

  if (!tcpClient.open()) {
    LOG(ERROR) << tcpClient.err;
    return EXIT_FAILURE;
  }

  return 0;
}
