#include "api_gateway_handler.h"
#include "client_server_connection.h"
#include "http_client_server_session.h"
#include "yamlcpp_config.h"
#include <memory>

int main(int argc, char *argv[]) {
  net::io_context ioc;
  std::shared_ptr<BaseConfig> config(new YamlCppConfig(argv[1]));

  auto handler_creator = std::shared_ptr<BaseClientServerReqHandlerCreator>(
      new ClientServerReqHandlerCreator<ApiGatewayHandler>(config));

  std::shared_ptr<ClientServerSessionCreator> creator(
      new HttpClientServerSessionCreator(handler_creator));

  std::shared_ptr<ClientServerConnection> con(
      new ClientServerConnection(ioc, creator, config));

  con->run();
  return 0;
}
