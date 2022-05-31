#include "workers_controller.h"
#include <iostream>
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

bool WorkersController::is_valid_session(size_t& worker_id,
                                         const std::string& token) {
  bool is_expired = token_generator_->check_expired(token);
  if (is_expired)
    return false;

  return auth_db_->is_valid_session(worker_id, token);
}

bool WorkersController::is_valid_access(
    size_t worker_id,
    const PrivilegeLevel& min_privilege_level) {
  auto worker = workers_db_->read(worker_id);
  return min_privilege_level >= worker.getPrivilege();
}

WorkerGet WorkersController::get_worker(size_t worker_id) {
  auto worker_base = workers_db_->read(worker_id);
  return WorkerGet(worker_id, worker_base);
}

void WorkersController::update_worker(const WorkerUpdate& worker) {
  WorkerUpdate worker_copy = worker;
  auto salt_password = encrypt_strategy_->encrypt(worker_copy.password());
  worker_copy.setPassword(salt_password);
  auto rc = workers_db_->update(worker_copy);
  if (rc != 0)
    throw NotUniqueUsernameException();
}
