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

size_t WorkersFacade::sign_up(WorkerPost& worker) {
  return workers_controller_->sign_up(worker);
}

void WorkersFacade::update_worker(const WorkerUpdate& worker) {
  workers_controller_->update_worker(worker);
}

void WorkersFacade::update_worker_privilege(size_t worker_id,
                                            const PrivilegeLevel& privelege) {
  workers_db_->update_privilege(worker_id, privelege);
}

WorkerGet WorkersFacade::get_worker(size_t worker_id) {
  return workers_controller_->get_worker(worker_id);
}

std::vector<WorkerGet> WorkersFacade::get_workers() {
  return workers_db_->read();
}

std::string WorkersFacade::login(const WorkerAuth& worker) {
  return workers_controller_->login(worker);
}

bool WorkersFacade::is_valid_session(size_t& worker_id,
                                     const std::string& token) {
  return workers_controller_->is_valid_session(worker_id, token);
}

bool WorkersFacade::is_valid_access(size_t worker_id,
                                    const PrivilegeLevel& min_privilege_level) {
  return workers_controller_->is_valid_access(worker_id, min_privilege_level);
}
