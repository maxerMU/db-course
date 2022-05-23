#ifndef POSTGRESAUTHREPOSITORY_H
#define POSTGRESAUTHREPOSITORY_H

#include <map>
#include <pqxx/pqxx>
#include "base_auth_repository.h"
#include "base_config.h"

class PostgresAuthRepository : public BaseAuthRepository {
 public:
  PostgresAuthRepository(const std::shared_ptr<BaseConfig>& conf,
                         const std::string& connection_section);
  virtual void create_session(size_t worker_id,
                              const std::string& token) override;
  virtual bool is_valid_session(size_t& worker_id,
                                const std::string& token) override;

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

  enum PreparedRequests { CREATE, IS_VALID };

  std::map<PreparedRequests, std::string> requests_names = {
      {CREATE, "create_new_session"},
      {IS_VALID, "check_valid"}};
};

#endif  // POSTGRESAUTHREPOSITORY_H
