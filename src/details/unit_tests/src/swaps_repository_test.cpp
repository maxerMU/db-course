#include "swaps_repository_test.h"
#include "database_exceptions.h"
#include "yamlcpp_config.h"

SwapsRepositoryTest::SwapsRepositoryTest() {
  std::shared_ptr<BaseConfig> config(new YamlCppConfig(ConfFileName));
  test_rep =
      std::shared_ptr<StockDbTest>(new StockDbTest(config, ConfStockDbSection));

  swaps_rep = std::shared_ptr<PostgresSwapsRepository>(
      new PostgresSwapsRepository(config, ConfSwapsDbSection));
}

void SwapsRepositoryTest::SetUp() {
  test_rep->clean_database();

  details_ = detail_mother_object.create_details();

  for (auto& detail : details_) {
    DetailsProducerData producer =
        producer_mother_object.create_producer_data();

    size_t producer_id = test_rep->create_producer(producer);
    detail.set_producer_id(producer_id);
    test_rep->create(detail);
  }
}

void SwapsRepositoryTest::TearDown() {
  test_rep->clean_database();
}

TEST_F(SwapsRepositoryTest, create_swap) {
  Detail detail_src = details_[0];
  Detail detail_dst = details_[details_.size() - 1];

  swaps_rep->create(detail_src.part_number(), detail_dst.part_number());

  auto swaps_res = test_rep->read_swap(detail_src.part_number());
  ASSERT_EQ(detail_dst.part_number(), swaps_res[0]);
}

TEST_F(SwapsRepositoryTest, read_swap) {
  Detail detail_src = details_[0];
  Detail detail_dst = details_[details_.size() - 1];
  test_rep->create_swap(detail_src.part_number(), detail_dst.part_number());

  auto swaps_res = swaps_rep->read(detail_src.part_number());

  ASSERT_EQ(detail_dst.part_number(), swaps_res[0]);
}

TEST_F(SwapsRepositoryTest, delete_swap) {
  Detail detail_src = details_[0];
  Detail detail_dst = details_[details_.size() - 1];
  test_rep->create_swap(detail_src.part_number(), detail_dst.part_number());

  swaps_rep->delete_(detail_src.part_number(), detail_dst.part_number());

  auto swaps_res = test_rep->read_swap(detail_src.part_number());
  ASSERT_TRUE(swaps_res.empty());
}
