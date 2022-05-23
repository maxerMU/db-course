#include "details_facade_test.h"
#include <cmath>
#include "base_config.h"
#include "details_facade.h"
#include "producer.h"

using ::testing::_;
using ::testing::Return;

void DetailsFacadeTests::SetUp() {
  producers_db_ =
      std::shared_ptr<ProducersMockRepository>(new ProducersMockRepository());

  details_db_ =
      std::shared_ptr<DetailsMockReposiroty>(new DetailsMockReposiroty());

  swaps_db_ = std::shared_ptr<SwapsMockRepository>(new SwapsMockRepository());

  stock_db_ = std::shared_ptr<StockMockRepository>(new StockMockRepository());

  std::shared_ptr<BaseConfig> conf;

  DetailsFacade::instanse().init(conf, producers_db_, details_db_, swaps_db_,
                                 stock_db_);
}

void DetailsFacadeTests::TearDown() {}

TEST_F(DetailsFacadeTests, create_producer) {
  DetailsProducerData producer_data("test", "test");
  EXPECT_CALL(*producers_db_, create(producer_data))
      .Times(1)
      .WillRepeatedly(Return(1));

  EXPECT_TRUE(DetailsFacade::instanse().add_producer(producer_data) == 1);
}

TEST_F(DetailsFacadeTests, read_producer) {
  DetailsProducer producer(1, "test", "test");
  EXPECT_CALL(*producers_db_, read(1))
      .Times(1)
      .WillRepeatedly(Return(producer));

  EXPECT_TRUE(DetailsFacade::instanse().get_producer(1) == producer);
}

TEST_F(DetailsFacadeTests, create_detail) {
  Detail detail("test", "test", "test", 1);

  EXPECT_CALL(*details_db_, create(detail)).Times(1);
  DetailsFacade::instanse().add_detail(detail);
}

TEST_F(DetailsFacadeTests, read_detail) {
  Detail detail("test", "test", "test", 1);

  EXPECT_CALL(*details_db_, read("test"))
      .Times(1)
      .WillRepeatedly(Return(detail));

  EXPECT_TRUE(DetailsFacade::instanse().get_detail("test") == detail);
}

TEST_F(DetailsFacadeTests, create_swap) {
  EXPECT_CALL(*swaps_db_, create("test", "test")).Times(1);
  DetailsFacade::instanse().add_detail_swap("test", "test");
}

TEST_F(DetailsFacadeTests, read_swaps) {
  std::vector<std::string> swaps{"test", "test", "test"};

  EXPECT_CALL(*swaps_db_, read("test")).Times(1).WillRepeatedly(Return(swaps));

  Detail detail("test", "test", "test", 1);
  EXPECT_CALL(*details_db_, read("test"))
      .Times(swaps.size())
      .WillRepeatedly(Return(detail));

  details_t details;
  for (size_t i = 0; i < swaps.size(); i++)
    details.push_back(detail);

  EXPECT_TRUE(DetailsFacade::instanse().get_detail_swaps("test") == details);
}

TEST_F(DetailsFacadeTests, add_to_stock) {
  size_t worker_id = 1;
  std::string part_number = "test";
  size_t quantity = 2;
  EXPECT_CALL(*stock_db_, create(part_number, worker_id, quantity)).Times(1);
  DetailsFacade::instanse().add_detail_to_stock(part_number, worker_id,
                                                quantity);
}

TEST_F(DetailsFacadeTests, stock_info) {
  detail_quantity_t quantity("test", 2);

  EXPECT_CALL(*stock_db_, read("test"))
      .Times(1)
      .WillRepeatedly(Return(quantity));

  EXPECT_TRUE(DetailsFacade::instanse().get_detail_in_stock("test") ==
              quantity);
}
