#ifndef DETAILSREPOSITORYTEST_H
#define DETAILSREPOSITORYTEST_H

#include <gtest/gtest.h>

#include <map>
#include <pqxx/pqxx>
#include "base_config.h"
#include "base_details_repository.h"
#include "postgres_details_repository.h"

const std::string ConfFileName = "conf/test.yaml";
const std::string ConfDetialsDbSection = "DB_DETAILS";

class PostgresDetailsTestRepository {
 public:
  PostgresDetailsTestRepository(const std::shared_ptr<BaseConfig>& conf,
                                const std::string& connection_section);

  virtual void create(const Detail& detail);
  virtual Detail read(const std::string& part_name);
  virtual void delete_(const std::string& part_name);

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

  enum PreparedRequests { CREATE, READ_BY_ID, DELETE };

  std::map<PreparedRequests, std::string> requests_names = {
      {CREATE, "create_detail"},
      {READ_BY_ID, "read_detail_by_id"},
      {DELETE, "delete_detail"}};
};

class DetailsRepositoryTest : public ::testing::Test {
 protected:
  void SetUp() override;
  void TearDown() override;

 public:
  std::shared_ptr<PostgresDetailsTestRepository> test_rep;
  std::shared_ptr<PostgresDetailsRepository> details_rep;
};

#endif  // DETAILSREPOSITORYTEST_H
