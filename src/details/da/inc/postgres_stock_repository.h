#ifndef POSTGRESSTOCKREPOSITORY_H
#define POSTGRESSTOCKREPOSITORY_H

#include <map>
#include <pqxx/pqxx>
#include "base_config.h"
#include "base_stock_repository.h"

class PostgresStockRepository : public BaseStockRepository {
 public:
  PostgresStockRepository(const std::shared_ptr<BaseConfig>& conf,
                          const std::string& connection_section);
  virtual void create(const std::string& part_name,
                      size_t worker_id,
                      size_t quantity) override;
  virtual detail_quantity_t read(const std::string& part_name) override;
  virtual details_quantities_t read_current() override;
  virtual stock_logs_t read_log(const std::string& time_start,
                                const std::string& time_end) override;
  virtual details_names_t read_prev() override;
  virtual void delete_(const std::string& part_name,
                       size_t worker_id,
                       size_t quantity) override;

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

  enum PreparedRequests { READ_CURR, READ_PREV, READ_BY_ID, READ_LOG, UPDATE };

  std::map<PreparedRequests, std::string> requests_names = {
      {UPDATE, "add_remove_details"},
      {READ_CURR, "read_current_details"},
      {READ_PREV, "read_previuos_details"},
      {READ_BY_ID, "read_detail_by_name"},
      {READ_LOG, "read_log"},
  };
};

#endif  // POSTGRESSTOCKREPOSITORY_H
