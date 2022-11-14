#ifndef STOCKLOGSREPOSITORYTEST_H
#define STOCKLOGSREPOSITORYTEST_H

#include <gtest/gtest.h>

#include "base_config.h"
#include "detail_mother_object.h"
#include "postgres_stock_repository.h"
#include "producer_mother_object.h"
#include "stock_db_test_repository.h"
#include "stock_log_data_builder.h"

class StockRepositoryTest : public ::testing::Test {
 public:
  StockRepositoryTest();

 protected:
  void SetUp() override;
  void TearDown() override;

 public:
  std::shared_ptr<StockDbTest> test_rep;
  std::shared_ptr<PostgresStockRepository> logs_rep;

  DetailMotherObject detail_mother_object;
  ProducerMotherObject producer_mother_object;
  StockLogDataBuilder stock_log_data_builder;

  details_t details_;
  size_t worker_id_;
};

#endif  // STOCKLOGSREPOSITORYTEST_H
