#ifndef SWAPSREPOSITORYTEST_H
#define SWAPSREPOSITORYTEST_H

#include <gtest/gtest.h>

#include "base_config.h"
#include "detail_mother_object.h"
#include "postgres_swaps_repository.h"
#include "producer_mother_object.h"
#include "stock_db_test_repository.h"

class SwapsRepositoryTest : public ::testing::Test {
 public:
  SwapsRepositoryTest();

 protected:
  void SetUp() override;
  void TearDown() override;

 public:
  std::shared_ptr<StockDbTest> test_rep;
  std::shared_ptr<PostgresSwapsRepository> swaps_rep;

  DetailMotherObject detail_mother_object;
  ProducerMotherObject producer_mother_object;

  details_t details_;
};

#endif  // SWAPSREPOSITORYTEST_H
