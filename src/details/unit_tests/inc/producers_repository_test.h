#ifndef PRODUCERSREPOSITORYTEST_H
#define PRODUCERSREPOSITORYTEST_H

#include <gtest/gtest.h>

#include "base_config.h"
#include "detail_mother_object.h"
#include "postgres_producers_repository.h"
#include "producer_mother_object.h"
#include "stock_db_test_repository.h"

class ProducersRepositoryTest : public ::testing::Test {
 public:
  ProducersRepositoryTest();

 protected:
  void SetUp() override;
  void TearDown() override;

 public:
  std::shared_ptr<StockDbTest> test_rep;
  std::shared_ptr<PostgresProducersRepository> producers_rep;

  ProducerMotherObject producer_mother_object_;
};

#endif // PRODUCERSREPOSITORYTEST_H
