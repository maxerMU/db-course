#include <boost/asio.hpp>
#include <memory>
#include "client_server_connection.h"
#include "details_facade.h"
#include "details_handler.h"
#include "echo_session.h"
#include "http_client_server_session.h"
#include "http_session.h"
#include "server_connection.h"
#include "yamlcpp_config.h"

int main(int argc, char* argv[]) {
  net::io_context ioc;
  std::shared_ptr<BaseConfig> config(new YamlCppConfig(argv[1]));

  auto producers_db = std::shared_ptr<BaseProducersRepository>(
      new PostgresProducersRepository(config, DbProducersSection));

  auto details_db = std::shared_ptr<BaseDetailsRepository>(
      new PostgresDetailsRepository(config, DbDetailsSection));

  auto swaps_db = std::shared_ptr<BaseSwapsRepository>(
      new PostgresSwapsRepository(config, DbSwapsSection));

  auto stock_db = std::shared_ptr<BaseStockRepository>(
      new PostgresStockRepository(config, DbStockSection));

  DetailsFacade::instanse().init(config, producers_db, details_db, swaps_db,
                                 stock_db);

  // auto handler_creator = std::shared_ptr<BaseServerReqHandlerCreator>(
  //     new ServerReqHandlerCreator<DetailsHandler>(config));

  // std::shared_ptr<ServerSessionCreator> creator(
  //     new HttpServerSessionCreator(handler_creator));

  // std::shared_ptr<ServerConnection> con(
  //     new ServerConnection(ioc, creator, config));

  // con->run();

  auto handler_creator = std::shared_ptr<BaseClientServerReqHandlerCreator>(
      new ClientServerReqHandlerCreator<DetailsAuthHandler>(config));

  std::shared_ptr<ClientServerSessionCreator> creator(
      new HttpClientServerSessionCreator(handler_creator));

  std::shared_ptr<ClientServerConnection> con(
      new ClientServerConnection(ioc, creator, config));

  con->run();

  return 0;
}
