#ifndef STOCKDBTEST_H
#define STOCKDBTEST_H

#include <map>
#include <pqxx/pqxx>
#include "base_config.h"
#include "base_details_repository.h"

const std::string ConfFileName = "conf/test.yaml";
const std::string ConfDetialsDbSection = "DB_DETAILS";
const std::string ConfProducersDbSection = "DB_PRODUCERS";
const std::string ConfSwapsDbSection = "DB_SWAPS";
const std::string ConfStockLogDbSection = "DB_STOCK_LOG";
const std::string ConfStockDbSection = "STOCK_DB";

class StockDbTest {
 public:
  StockDbTest(const std::shared_ptr<BaseConfig>& conf,
              const std::string& connection_section);

  virtual void create(const Detail& detail);
  virtual Detail read(const std::string& part_name);
  virtual void delete_(const std::string& part_name);

  virtual size_t create_producer(const DetailsProducerData& producer);
  virtual DetailsProducer read_producer(size_t producer_id);

  virtual void create_swap(const std::string& src, const std::string& dst);
  virtual details_names_t read_swap(const std::string& src);

  virtual void create_log(const std::string& part_name,
                          size_t worker_id,
                          size_t quantity);
  virtual detail_quantity_t read_log(const std::string& part_name);
  virtual void delete_log(const std::string& part_name,
                          size_t worker_id,
                          size_t quantity);

  virtual size_t create_test_worker();

  virtual void clean_database();

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

  enum PreparedRequests {
    CREATE,
    READ_BY_ID,
    DELETE,
    CREATE_PRODUCER,
    READ_PRODUCER,
    CREATE_SWAP,
    READ_SWAP,
    UPDATE_LOG,
    READ_LOG,
    CREATE_WORKER,
    CLEAN
  };

  std::map<PreparedRequests, std::string> requests_names = {
      {CREATE, "create_detail"},        {READ_BY_ID, "read_detail_by_id"},
      {DELETE, "delete_detail"},        {CREATE_PRODUCER, "create_producer"},
      {READ_PRODUCER, "read_producer"}, {CREATE_SWAP, "create_swap"},
      {READ_SWAP, "read_swap"},         {UPDATE_LOG, "create_log"},
      {READ_LOG, "read_log"},           {CREATE_WORKER, "create_worker"},
      {CLEAN, "clean_database"}};
};

#endif  // STOCKDBTEST_H
