#include "workers_controller.h"
#include "logic_exceptions.h"

WorkersController::WorkersController(
    const std::shared_ptr<BaseEncryptStrategy>& encrypt_strategy,
    const std::shared_ptr<BaseTokenGenerator>& token_generator,
    const std::shared_ptr<BaseAuthRepository>& auth_db,
    const std::shared_ptr<BaseWorkersRepository>& workers_db)
    : encrypt_strategy_(encrypt_strategy),
      token_generator_(token_generator),
      auth_db_(auth_db),
      workers_db_(workers_db) {}

void WorkersController::sign_up(WorkerPost& worker) {
  size_t workers_count = workers_db_->workers_count();
  if (workers_count == 0) {
    worker.setPrivilege(ADMIN);
  } else {
    worker.setPrivilege(CLIENT);
  }

  auto salt_password = encrypt_strategy_->encrypt(worker.password());
  worker.setPassword(salt_password);

  auto rc = workers_db_->create(worker);
  if (rc != 0)
    throw NotUniqueUsernameException();
}

std::string WorkersController::login(const WorkerAuth& worker) {
  std::string password;
  size_t worker_id;
  bool is_valid_username =
      workers_db_->get_password(password, worker_id, worker.username());

  if (!is_valid_username)
    throw InvalidAuthDataException("Invalid username");

  auto salt_password = encrypt_strategy_->encrypt(worker.password());
  if (salt_password != password)
    throw InvalidAuthDataException("Invalid password");

  auto token = token_generator_->generate_token();
  auth_db_->create_session(worker_id, token);

  return token;
}
