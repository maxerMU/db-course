#ifndef WORKERSFACADE_H
#define WORKERSFACADE_H

#include <memory>
#include <vector>
#include "base_config.h"
#include "postgres_auth_repository.h"
#include "postgres_workers_repository.h"
#include "redis_auth_repository.h"
#include "reqresp.h"
#include "worker.h"
#include "workers_controller.h"

const std::string DbWorkersSection = "DB_WORKERS";
// const std::string DbAuthSection = "DB_AUTH_REDIS";
const std::string EncryptSection = "ENCRYPT";
const std::string AuthSection = "AUTH";
const std::string SelectAuthDbSection = "DB_AUTH_SECTION";

class WorkersFacade {
 private:
  WorkersFacade();
  WorkersFacade(const WorkersFacade&) = delete;

 public:
  static WorkersFacade& instanse() {
    static WorkersFacade facade;
    return facade;
  }

  void init(const std::shared_ptr<BaseConfig>& conf,
            const std::shared_ptr<BaseWorkersRepository>& workers_rep,
            const std::shared_ptr<BaseAuthRepository>& auth_rep,
            const std::shared_ptr<WorkersController>& workers_controller);

  /* workers */
  void sign_up(WorkerPost& worker);
  std::string login(const WorkerAuth& worker);
  bool is_valid_session(size_t& worker_id, const std::string& token);
  bool is_valid_access(size_t worker_id,
                       const std::string& target,
                       const method_t& method);

 private:
  std::shared_ptr<BaseConfig> config_;
  std::shared_ptr<WorkersController> workers_controller_;
  std::shared_ptr<BaseWorkersRepository> workers_db_;
  std::shared_ptr<BaseAuthRepository> auth_db_;
};

#endif  // WORKERSFACADE_H
