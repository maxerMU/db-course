#ifndef POSTGRESDETAILSREPOSITORY_H
#define POSTGRESDETAILSREPOSITORY_H

#include <map>
#include <pqxx/pqxx>
#include "base_config.h"
#include "base_details_repository.h"

class PostgresDetailsRepository : public BaseDetailsRepository {
 public:
  PostgresDetailsRepository(const std::shared_ptr<BaseConfig>& conf,
                            const std::string& connection_section);

  virtual void create(const Detail& detail) override;
  virtual Detail read(const std::string& part_name) override;
  virtual details_t read_all() override;
  virtual void update(const Detail& detail) override;
  virtual void delete_(const std::string& part_name) override;

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

  enum PreparedRequests { CREATE, READ_ALL, READ_BY_ID, UPDATE, DELETE };

  std::map<PreparedRequests, std::string> requests_names = {
      {CREATE, "create_detail"},
      {READ_ALL, "read_all_details"},
      {READ_BY_ID, "read_detail_by_id"},
      {UPDATE, "update_detail"},
      {DELETE, "delete_detail"}};
};

#endif  // POSTGRESDETAILSREPOSITORY_H
