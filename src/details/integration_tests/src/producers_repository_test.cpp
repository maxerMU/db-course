#include "producers_repository_test.h"
#include "database_exceptions.h"
#include "yamlcpp_config.h"

ProducersRepositoryTest::ProducersRepositoryTest() {
  std::shared_ptr<BaseConfig> config(new YamlCppConfig(ConfFileName));
  test_rep =
      std::shared_ptr<StockDbTest>(new StockDbTest(config, ConfStockDbSection));

  producers_rep = std::shared_ptr<PostgresProducersRepository>(
      new PostgresProducersRepository(config, ConfProducersDbSection));
}

void ProducersRepositoryTest::SetUp() {
  test_rep->clean_database();
}

void ProducersRepositoryTest::TearDown() {
  test_rep->clean_database();
}

TEST_F(ProducersRepositoryTest, create_producer) {
  DetailsProducerData producer = producer_mother_object_.create_producer_data();

  size_t producer_id = producers_rep->create(producer);

  auto producer_res = test_rep->read_producer(producer_id);
  ASSERT_TRUE(producer_res.country() == producer.country());
  ASSERT_TRUE(producer_res.name() == producer.name());
}

TEST_F(ProducersRepositoryTest, read_producer) {
  DetailsProducerData producer = producer_mother_object_.create_producer_data();
  size_t producer_id = test_rep->create_producer(producer);

  auto producer_res = producers_rep->read(producer_id);

  ASSERT_TRUE(producer_res.country() == producer.country());
  ASSERT_TRUE(producer_res.name() == producer.name());
}

TEST_F(ProducersRepositoryTest, update_producer) {
  DetailsProducerData producer = producer_mother_object_.create_producer_data();
  size_t producer_id = test_rep->create_producer(producer);
  DetailsProducer producer_updated(
      producer_id, producer.country() + producer.name(), producer.country());

  producers_rep->update(producer_updated);

  auto producer_res = test_rep->read_producer(producer_id);
  ASSERT_TRUE(producer_res.country() == producer_updated.country());
  ASSERT_TRUE(producer_res.name() == producer_updated.name());
}

TEST_F(ProducersRepositoryTest, delete_producer) {
  DetailsProducerData producer = producer_mother_object_.create_producer_data();
  size_t producer_id = test_rep->create_producer(producer);

  producers_rep->delete_(producer_id);

  EXPECT_THROW(test_rep->read_producer(producer_id), DatabaseNotFoundException);
}
