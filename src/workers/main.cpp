#include <boost/asio.hpp>
#include <memory>
#include "echo_session.h"
#include "http_session.h"
#include "jwt_token_generator.h"
#include "server_connection.h"
#include "workers_facade.h"
#include "workers_handler.h"
#include "yamlcpp_config.h"

int main(int argc, char* argv[]) {
  net::io_context ioc;
  std::shared_ptr<BaseConfig> config(new YamlCppConfig(argv[1]));
  auto workers_db = std::shared_ptr<BaseWorkersRepository>(
      new PostgresWorkersRepository(config, DbWorkersSection));

  auto auth_section = config->get_string_field({SelectAuthDbSection});

  auto auth_db = std::shared_ptr<BaseAuthRepository>(
      new RedisAuthRepository(config, auth_section));

  auto encrypt_strategy = std::shared_ptr<BaseEncryptStrategy>(
      new SHA256Encrypt(config, EncryptSection));

  auto token_generator = std::shared_ptr<BaseTokenGenerator>(
      new JWTTokenGenerator(config, AuthSection));

  auto workers_controller =
      std::shared_ptr<WorkersController>(new WorkersController(
          encrypt_strategy, token_generator, auth_db, workers_db));

  WorkersFacade::instanse().init(config, workers_db, auth_db,
                                 workers_controller);

  auto handler_creator = std::shared_ptr<BaseServerReqHandlerCreator>(
      new ServerReqHandlerCreator<WorkersHandler>(config));

  std::shared_ptr<ServerSessionCreator> creator(
      new HttpServerSessionCreator(handler_creator));

  std::shared_ptr<ServerConnection> con(
      new ServerConnection(ioc, creator, config));

  con->run();
  return 0;
}
