#include "details_facade_test.h"
#include <cmath>
#include "base_config.h"
#include "database_exceptions.h"
#include "details_facade.h"
#include "producer.h"
#include "stock_log_data_builder.h"
#include "yamlcpp_config.h"

DetailsFacadeTests::DetailsFacadeTests() {
  std::shared_ptr<BaseConfig> config(new YamlCppConfig(ConfFileName));
  conf = config;

  test_rep =
      std::shared_ptr<StockDbTest>(new StockDbTest(config, ConfStockDbSection));

  producers_db_ = std::shared_ptr<PostgresProducersRepository>(
      new PostgresProducersRepository(config, ConfProducersDbSection));

  details_db_ = std::shared_ptr<PostgresDetailsRepository>(
      new PostgresDetailsRepository(config, ConfDetialsDbSection));

  swaps_db_ = std::shared_ptr<PostgresSwapsRepository>(
      new PostgresSwapsRepository(config, ConfSwapsDbSection));

  stock_db_ = std::shared_ptr<PostgresStockRepository>(
      new PostgresStockRepository(config, ConfStockDbSection));

  producer_mother_object_ = ProducerMotherObject();
  detail_mother_object_ = DetailMotherObject();
}

void DetailsFacadeTests::SetUp() {
  test_rep->clean_database();
  DetailsFacade::instanse().init(conf, producers_db_, details_db_, swaps_db_,
                                 stock_db_);
}

void DetailsFacadeTests::TearDown() {
  test_rep->clean_database();
}

TEST_F(DetailsFacadeTests, create_producer) {
  DetailsProducerData producer_data =
      producer_mother_object_.create_producer_data();

  size_t id = DetailsFacade::instanse().add_producer(producer_data);

  EXPECT_TRUE(id == 1);
}

TEST_F(DetailsFacadeTests, read_producer) {
  DetailsProducerData producer = producer_mother_object_.create_producer_data();
  test_rep->create_producer(producer);
  DetailsProducer expected_res = DetailsProducer(1, producer);

  DetailsProducer res = DetailsFacade::instanse().get_producer(1);

  EXPECT_TRUE(res == expected_res);
}

TEST_F(DetailsFacadeTests, read_producers) {
  auto producers = producer_mother_object_.create_producers_data();
  producers_t expected_res;
  for (size_t i = 0; i < producers.size(); i++) {
    expected_res.push_back(DetailsProducer(i + 1, producers[i]));
    test_rep->create_producer(producers[i]);
  }

  producers_t res = DetailsFacade::instanse().get_producers();

  EXPECT_TRUE(res == expected_res);
}

TEST_F(DetailsFacadeTests, delete_producer) {
  DetailsProducerData producer = producer_mother_object_.create_producer_data();
  size_t producer_id = test_rep->create_producer(producer);

  DetailsFacade::instanse().delete_producer(producer_id);

  EXPECT_THROW(test_rep->read_producer(producer_id), DatabaseNotFoundException);
}

TEST_F(DetailsFacadeTests, create_detail) {
  DetailsProducerData producer = producer_mother_object_.create_producer_data();
  size_t producer_id = test_rep->create_producer(producer);
  Detail detail = detail_mother_object_.create_detail();
  detail.set_producer_id(producer_id);

  DetailsFacade::instanse().add_detail(detail);

  auto read_detail = test_rep->read(detail.part_number());
  ASSERT_TRUE(detail == read_detail);
}

TEST_F(DetailsFacadeTests, read_detail) {
  DetailsProducerData producer = producer_mother_object_.create_producer_data();
  size_t producer_id = test_rep->create_producer(producer);
  Detail detail = detail_mother_object_.create_detail();
  detail.set_producer_id(producer_id);
  test_rep->create(detail);

  Detail res = DetailsFacade::instanse().get_detail(detail.part_number());

  EXPECT_TRUE(res == detail);
}

TEST_F(DetailsFacadeTests, update_detail) {
  DetailsProducerData producer = producer_mother_object_.create_producer_data();
  size_t producer_id = test_rep->create_producer(producer);
  Detail detail = detail_mother_object_.create_detail();
  detail.set_producer_id(producer_id);
  test_rep->create(detail);
  detail.set_name_rus(detail.name_rus() + detail.name_eng());

  DetailsFacade::instanse().update_detail(detail);

  auto read_detail = test_rep->read(detail.part_number());
  ASSERT_TRUE(detail == read_detail);
}

TEST_F(DetailsFacadeTests, delete_detail) {
  DetailsProducerData producer = producer_mother_object_.create_producer_data();
  size_t producer_id = test_rep->create_producer(producer);
  Detail detail = detail_mother_object_.create_detail();
  detail.set_producer_id(producer_id);
  test_rep->create(detail);

  DetailsFacade::instanse().delete_detail(detail.part_number());

  EXPECT_THROW(test_rep->read(detail.part_number()), DatabaseNotFoundException);
}
