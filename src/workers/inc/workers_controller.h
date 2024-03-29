#ifndef WORKERSCONTROLLER_H
#define WORKERSCONTROLLER_H

#include <memory>
#include "base_auth_repository.h"
#include "base_workers_repository.h"
#include "reqresp.h"
#include "sha256_encrypt.h"
#include "token_generator.h"

class WorkersController {
 public:
  WorkersController(
      const std::shared_ptr<BaseEncryptStrategy>& encrypt_strategy,
      const std::shared_ptr<BaseTokenGenerator>& token_generator,
      const std::shared_ptr<BaseAuthRepository>& auth_db,
      const std::shared_ptr<BaseWorkersRepository>& workers_db);

  size_t sign_up(WorkerPost& worker);
  std::string login(const WorkerAuth& worker);
  bool is_valid_session(size_t& worker_id, const std::string& token);
  bool is_valid_access(size_t worker_id,
                       const PrivilegeLevel& min_privilege_level);
  WorkerGet get_worker(size_t worker_id);
  void update_worker(const WorkerUpdate& worker);

 private:
  std::shared_ptr<BaseEncryptStrategy> encrypt_strategy_;
  std::shared_ptr<BaseTokenGenerator> token_generator_;
  std::shared_ptr<BaseAuthRepository> auth_db_;
  std::shared_ptr<BaseWorkersRepository> workers_db_;
};

#endif  // WORKERSCONTROLLER_H
