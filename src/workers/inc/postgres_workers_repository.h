#ifndef POSTGRESWORKERSREPOSITORY_H
#define POSTGRESWORKERSREPOSITORY_H

#include <map>
#include <pqxx/pqxx>
#include "base_config.h"
#include "base_workers_repository.h"

class PostgresWorkersRepository : public BaseWorkersRepository {
 public:
  PostgresWorkersRepository(const std::shared_ptr<BaseConfig>& conf,
                            const std::string& connection_section);

  virtual int create(const WorkerPost& worker) override;
  virtual size_t workers_count() override;
  virtual void update(const WorkerUpdate& worker) override;
  virtual bool get_password(std::string& password,
                            size_t& worker_id,
                            const std::string& username) override;

 private:
  void read_config(const std::shared_ptr<BaseConfig>& conf,
                   const std::string& connection_section);

  void connect();
  void add_prepare_statements();

  std::shared_ptr<pqxx::connection> connection_;

  std::string name_;
  std::string user_;
  std::string user_password_;
  std::string host_;
  size_t port_;

  enum PreparedRequests { CREATE, READ_COUNT, READ_PASSWORD, UPDATE };

  std::map<PreparedRequests, std::string> requests_names = {
      {CREATE, "create_worker"},
      {READ_COUNT, "read_workers_count"},
      {READ_PASSWORD, "read_password"},
      {UPDATE, "update_worker"}};
};

#endif  // POSTGRESWORKERSREPOSITORY_H
