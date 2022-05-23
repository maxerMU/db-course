#pragma once

#include <gtest/gtest.h>
#include "mock_repositories.h"

class DetailsFacadeTests : public ::testing::Test {
 protected:
  void SetUp() override;
  void TearDown() override;

 public:
  std::shared_ptr<ProducersMockRepository> producers_db_;
  std::shared_ptr<DetailsMockReposiroty> details_db_;
  std::shared_ptr<SwapsMockRepository> swaps_db_;
  std::shared_ptr<StockMockRepository> stock_db_;
};
