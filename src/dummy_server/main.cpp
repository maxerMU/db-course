#include "dummy_server_handler.h"
#include "echo_session.h"
#include "http_session.h"
#include "server_connection.h"
#include "yamlcpp_config.h"
#include <boost/asio.hpp>
#include <memory>

int main(int argc, char *argv[]) {
  net::io_context ioc;
  std::shared_ptr<BaseConfig> config(new YamlCppConfig(argv[1]));

  std::shared_ptr<ServerReqHandler> handler(
      new DummyServerHandler(ioc, config));

  std::shared_ptr<ServerSessionCreator> creator(
      new HttpServerSessionCreator(handler));

  std::shared_ptr<ServerConnection> con(
      new ServerConnection(ioc, creator, config));

  con->run();
  return 0;
}
