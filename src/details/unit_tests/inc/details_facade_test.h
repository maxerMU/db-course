#pragma once

#include <gtest/gtest.h>
#include "detail_mother_object.h"
#include "mock_repositories.h"
#include "producer_mother_object.h"

class DetailsFacadeTests : public ::testing::Test {
 protected:
  void SetUp() override;
  void TearDown() override;

 public:
  std::shared_ptr<ProducersMockRepository> producers_db_;
  std::shared_ptr<DetailsMockReposiroty> details_db_;
  std::shared_ptr<SwapsMockRepository> swaps_db_;
  std::shared_ptr<StockMockRepository> stock_db_;

  ProducerMotherObject producer_mother_object_;
  DetailMotherObject detail_mother_object_;
};
