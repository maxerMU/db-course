#include "workers_facade.h"
#include "jwt_token_generator.h"

WorkersFacade::WorkersFacade() {}

void WorkersFacade::init(const std::shared_ptr<BaseConfig>& conf) {
  config_ = conf;

  workers_db_ = std::shared_ptr<BaseWorkersRepository>(
      new PostgresWorkersRepository(conf, DbWorkersSection));

  auth_db_ = std::shared_ptr<BaseAuthRepository>(
      new PostgresAuthRepository(conf, DbAuthSection));

  auto encrypt_strategy = std::shared_ptr<BaseEncryptStrategy>(
      new SHA256Encrypt(conf, EncryptSection));

  auto token_generator = std::shared_ptr<BaseTokenGenerator>(
      new JWTTokenGenerator(conf, AuthSection));

  workers_controller_ =
      std::shared_ptr<WorkersController>(new WorkersController(
          encrypt_strategy, token_generator, auth_db_, workers_db_));
}

void WorkersFacade::sign_up(WorkerPost& worker) {
  workers_controller_->sign_up(worker);
}

std::string WorkersFacade::login(const WorkerAuth& worker) {
  return workers_controller_->login(worker);
}
