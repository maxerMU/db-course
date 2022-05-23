#include "workers_facade.h"
#include "jwt_token_generator.h"

WorkersFacade::WorkersFacade() {}

void WorkersFacade::init(
    const std::shared_ptr<BaseConfig>& conf,
    const std::shared_ptr<BaseWorkersRepository>& workers_rep,
    const std::shared_ptr<BaseAuthRepository>& auth_rep,
    const std::shared_ptr<WorkersController>& workers_controller) {
  config_ = conf;
  workers_db_ = workers_rep;
  auth_db_ = auth_rep;
  workers_controller_ = workers_controller;
}

void WorkersFacade::sign_up(WorkerPost& worker) {
  workers_controller_->sign_up(worker);
}

std::string WorkersFacade::login(const WorkerAuth& worker) {
  return workers_controller_->login(worker);
}

bool WorkersFacade::is_valid_session(size_t& worker_id,
                                     const std::string& token) {
  return workers_controller_->is_valid_session(worker_id, token);
}

bool WorkersFacade::is_valid_access(size_t worker_id,
                                    const std::string& target,
                                    const method_t& method) {
  return workers_controller_->is_valid_access(worker_id, target, method);
}
