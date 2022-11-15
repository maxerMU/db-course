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
//
// TEST_F(DetailsFacadeTests, create_swap) {
//   Detail detail_src = detail_mother_object_.create_detail();
//   Detail detail_dst = detail_mother_object_.create_detail();
//
//   EXPECT_CALL(*swaps_db_,
//               create(detail_src.part_number(), detail_dst.part_number()))
//       .Times(1);
//
//   DetailsFacade::instanse().add_detail_swap(detail_src.part_number(),
//                                             detail_dst.part_number());
// }
//
// TEST_F(DetailsFacadeTests, read_swaps) {
//   Detail detail_src = detail_mother_object_.create_detail();
//   details_t res = detail_mother_object_.create_details();
//
//   std::vector<std::string> swaps;
//   for (auto detail : res) {
//     swaps.push_back(detail.part_number());
//
//     EXPECT_CALL(*details_db_, read(detail.part_number()))
//         .Times(1)
//         .WillRepeatedly(Return(detail));
//   }
//
//   EXPECT_CALL(*swaps_db_, read(detail_src.part_number()))
//       .Times(1)
//       .WillRepeatedly(Return(swaps));
//
//   details_t details =
//       DetailsFacade::instanse().get_detail_swaps(detail_src.part_number());
//
//   EXPECT_TRUE(res == details);
// }
//
// TEST_F(DetailsFacadeTests, remove_swap) {
//   Detail detail_src = detail_mother_object_.create_detail();
//   Detail detail_dst = detail_mother_object_.create_detail();
//
//   EXPECT_CALL(*swaps_db_,
//               delete_(detail_src.part_number(), detail_dst.part_number()))
//       .Times(1);
//
//   DetailsFacade::instanse().delete_detail_swap(detail_src.part_number(),
//                                                detail_dst.part_number());
// }
//
// TEST_F(DetailsFacadeTests, add_to_stock) {
//   StockLog stock_log = StockLogDataBuilder()
//                            .with_fk_worker(1)
//                            ->with_fk_detail("test")
//                            ->with_change(2)
//                            ->build();
//   EXPECT_CALL(*stock_db_, create(stock_log.fk_detail(),
//   stock_log.fk_worker(),
//                                  stock_log.change()))
//       .Times(1);
//
//   DetailsFacade::instanse().add_detail_to_stock(
//       stock_log.fk_detail(), stock_log.fk_worker(), stock_log.change());
// }
//
// TEST_F(DetailsFacadeTests, remove_from_stock) {
//   StockLog stock_log = StockLogDataBuilder()
//                            .with_fk_worker(1)
//                            ->with_fk_detail("test")
//                            ->with_change(2)
//                            ->build();
//
//   EXPECT_CALL(*stock_db_, delete_(stock_log.fk_detail(),
//   stock_log.fk_worker(),
//                                   stock_log.change()))
//       .Times(1);
//
//   DetailsFacade::instanse().remove_detail_from_stock(
//       stock_log.fk_detail(), stock_log.fk_worker(), stock_log.change());
// }
//
// TEST_F(DetailsFacadeTests, stock_info) {
//   StockLog stock_log =
//       StockLogDataBuilder().with_fk_detail("test")->with_change(2)->build();
//   detail_quantity_t quantity(stock_log.fk_detail(), stock_log.change());
//
//   EXPECT_CALL(*stock_db_, read(stock_log.fk_detail()))
//       .Times(1)
//       .WillRepeatedly(Return(quantity));
//
//   detail_quantity_t res =
//       DetailsFacade::instanse().get_detail_in_stock(stock_log.fk_detail());
//   EXPECT_TRUE(quantity == res);
// }
//
// TEST_F(DetailsFacadeTests, stock_prev_details) {
//   details_t details = detail_mother_object_.create_details();
//   details_names_t names(details.size());
//   std::transform(details.data(), details.data() + details.size(),
//   names.data(),
//                  [](const Detail& d) { return d.part_number(); });
//
//   EXPECT_CALL(*stock_db_,
//   read_prev()).Times(1).WillRepeatedly(Return(names));
//
//   details_names_t res =
//   DetailsFacade::instanse().get_prev_details_in_stock(); EXPECT_TRUE(names ==
//   res);
// }
//
// TEST_F(DetailsFacadeTests, stock_current_details) {
//   details_quantities_t quantities =
//       detail_mother_object_.create_detail_quanties();
//
//   EXPECT_CALL(*stock_db_, read_current())
//       .Times(1)
//       .WillRepeatedly(Return(quantities));
//
//   details_quantities_t res =
//   DetailsFacade::instanse().get_details_in_stock(); EXPECT_TRUE(quantities ==
//   res);
// }
