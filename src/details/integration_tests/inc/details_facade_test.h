#ifndef DETAILSFACADETEST_H
#define DETAILSFACADETEST_H

#include <gtest/gtest.h>
#include "detail_mother_object.h"
#include "producer_mother_object.h"
#include "stock_db_test_repository.h"

#include "postgres_details_repository.h"
#include "postgres_producers_repository.h"
#include "postgres_stock_repository.h"
#include "postgres_swaps_repository.h"

class DetailsFacadeTests : public ::testing::Test {
 protected:
  void SetUp() override;
  void TearDown() override;

 public:
  DetailsFacadeTests();

  std::shared_ptr<BaseProducersRepository> producers_db_;
  std::shared_ptr<BaseDetailsRepository> details_db_;
  std::shared_ptr<BaseSwapsRepository> swaps_db_;
  std::shared_ptr<BaseStockRepository> stock_db_;
  std::shared_ptr<StockDbTest> test_rep;

  ProducerMotherObject producer_mother_object_;
  DetailMotherObject detail_mother_object_;

  std::shared_ptr<BaseConfig> conf;
};

#endif  // DETAILSFACADETEST_H
