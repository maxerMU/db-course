#ifndef POSTGRESSWAPSREPOSITORY_H
#define POSTGRESSWAPSREPOSITORY_H

#include <map>
#include <pqxx/pqxx>
#include "base_config.h"
#include "base_swaps_repository.h"

class PostgresSwapsRepository : public BaseSwapsRepository {
 public:
  PostgresSwapsRepository(const std::shared_ptr<BaseConfig>& conf,
                          const std::string& connection_section);

 public:
  virtual void create(const std::string& src, const std::string& dst) override;
  virtual details_names_t read(const std::string& src) override;
  virtual void delete_(const std::string& src, const std::string& dst) override;

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

  enum PreparedRequests { CREATE, READ, DELETE };

  std::map<PreparedRequests, std::string> requests_names = {
      {CREATE, "add_swap"},
      {READ, "get_swaps_for_detail"},
      {DELETE, "delete_swap"}};
};

#endif  // POSTGRESSWAPSREPOSITORY_H
