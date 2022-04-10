#include "details_handler.h"
#include "echo_session.h"
#include "http_session.h"
#include "server_connection.h"
#include "yamlcpp_config.h"
#include <boost/asio.hpp>
#include <memory>

int main(int argc, char *argv[]) {
  net::io_context ioc;
  std::shared_ptr<BaseConfig> config(new YamlCppConfig(argv[1]));

  auto handler_creator = std::shared_ptr<BaseServerReqHandlerCreator>(
      new ServerReqHandlerCreator<DetailsHandler>(config));

  std::shared_ptr<ServerSessionCreator> creator(
      new HttpServerSessionCreator(handler_creator));

  std::shared_ptr<ServerConnection> con(
      new ServerConnection(ioc, creator, config));

  con->run();
  return 0;
}
