#include <iostream>
#include <GTcpClient>

using namespace std;

int main() {
  GTcpClient tcpClient;
  tcpClient.host_ = "127.0.0.1";
  tcpClient.port_ = 10065;

  if (!tcpClient.open()) {
    clog << tcpClient.err << endl;
    return EXIT_FAILURE;
  }

  return 0;
}
