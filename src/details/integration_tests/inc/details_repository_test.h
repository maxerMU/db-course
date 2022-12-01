#ifndef DETAILSREPOSITORYTEST_H
#define DETAILSREPOSITORYTEST_H

#include <gtest/gtest.h>

#include "base_config.h"
#include "detail_mother_object.h"
#include "postgres_details_repository.h"
#include "producer_mother_object.h"
#include "stock_db_test_repository.h"

class DetailsRepositoryTest : public ::testing::Test {
 public:
  DetailsRepositoryTest();

 protected:
  void SetUp() override;
  void TearDown() override;

 public:
  std::shared_ptr<StockDbTest> test_rep;
  std::shared_ptr<PostgresDetailsRepository> details_rep;

  DetailMotherObject detail_mother_object_;
  ProducerMotherObject producer_mother_object_;
};

#endif  // DETAILSREPOSITORYTEST_H
