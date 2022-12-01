#include "details_facade_test.h"

#include <cmath>

#include "base_config.h"
#include "details_facade.h"
#include "producer.h"
#include "stock_log_data_builder.h"

using ::testing::_;
using ::testing::Return;

void DetailsFacadeTests::SetUp() {
  producers_db_ =
      std::shared_ptr<ProducersMockRepository>(new ProducersMockRepository());

  details_db_ =
      std::shared_ptr<DetailsMockReposiroty>(new DetailsMockReposiroty());

  swaps_db_ = std::shared_ptr<SwapsMockRepository>(new SwapsMockRepository());

  stock_db_ = std::shared_ptr<StockMockRepository>(new StockMockRepository());

  producer_mother_object_ = ProducerMotherObject();
  detail_mother_object_ = DetailMotherObject();

  std::shared_ptr<BaseConfig> conf;

  DetailsFacade::instanse().init(conf, producers_db_, details_db_, swaps_db_,
                                 stock_db_);
}

void DetailsFacadeTests::TearDown() {}

TEST_F(DetailsFacadeTests, create_producer) {
  DetailsProducerData producer_data =
      producer_mother_object_.create_producer_data();
  EXPECT_CALL(*producers_db_, create(producer_data))
      .Times(1)
      .WillRepeatedly(Return(1));

  size_t id = DetailsFacade::instanse().add_producer(producer_data);

  EXPECT_TRUE(id == 1);
}

TEST_F(DetailsFacadeTests, read_producer) {
  DetailsProducer producer = producer_mother_object_.create_producer();
  EXPECT_CALL(*producers_db_, read(producer.id()))
      .Times(1)
      .WillRepeatedly(Return(producer));

  DetailsProducer res = DetailsFacade::instanse().get_producer(1);

  EXPECT_TRUE(res == producer);
}

TEST_F(DetailsFacadeTests, read_producers) {
  producers_t producers = producer_mother_object_.create_producers();
  EXPECT_CALL(*producers_db_, read_all())
      .Times(1)
      .WillRepeatedly(Return(producers));

  producers_t res = DetailsFacade::instanse().get_producers();

  EXPECT_TRUE(res == producers);
}

TEST_F(DetailsFacadeTests, delete_producer) {
  DetailsProducer producer = producer_mother_object_.create_producer();
  EXPECT_CALL(*producers_db_, delete_(producer.id())).Times(1);

  DetailsFacade::instanse().delete_producer(producer.id());
}

TEST_F(DetailsFacadeTests, create_detail) {
  Detail detail = detail_mother_object_.create_detail();

  EXPECT_CALL(*details_db_, create(detail)).Times(1);
  DetailsFacade::instanse().add_detail(detail);
}

TEST_F(DetailsFacadeTests, read_detail) {
  Detail detail = detail_mother_object_.create_detail();
  EXPECT_CALL(*details_db_, read(detail.part_number()))
      .Times(1)
      .WillRepeatedly(Return(detail));

  Detail res = DetailsFacade::instanse().get_detail(detail.part_number());

  EXPECT_TRUE(res == detail);
}

TEST_F(DetailsFacadeTests, read_details) {
  details_t details = detail_mother_object_.create_details();

  EXPECT_CALL(*details_db_, read_all())
      .Times(1)
      .WillRepeatedly(Return(details));

  details_t res = DetailsFacade::instanse().get_details();

  EXPECT_TRUE(res == details);
}

TEST_F(DetailsFacadeTests, update_detail) {
  Detail detail = detail_mother_object_.create_detail();

  EXPECT_CALL(*details_db_, update(detail)).Times(1);
  DetailsFacade::instanse().update_detail(detail);
}

TEST_F(DetailsFacadeTests, delete_detail) {
  Detail detail = detail_mother_object_.create_detail();

  EXPECT_CALL(*details_db_, delete_(detail.part_number())).Times(1);
  DetailsFacade::instanse().delete_detail(detail.part_number());
}

TEST_F(DetailsFacadeTests, create_swap) {
  Detail detail_src = detail_mother_object_.create_detail();
  Detail detail_dst = detail_mother_object_.create_detail();

  EXPECT_CALL(*swaps_db_,
              create(detail_src.part_number(), detail_dst.part_number()))
      .Times(1);

  DetailsFacade::instanse().add_detail_swap(detail_src.part_number(),
                                            detail_dst.part_number());
}

TEST_F(DetailsFacadeTests, read_swaps) {
  Detail detail_src = detail_mother_object_.create_detail();
  details_t res = detail_mother_object_.create_details();

  std::vector<std::string> swaps;
  for (auto detail : res) {
    swaps.push_back(detail.part_number());

    EXPECT_CALL(*details_db_, read(detail.part_number()))
        .Times(1)
        .WillRepeatedly(Return(detail));
  }

  EXPECT_CALL(*swaps_db_, read(detail_src.part_number()))
      .Times(1)
      .WillRepeatedly(Return(swaps));

  details_t details =
      DetailsFacade::instanse().get_detail_swaps(detail_src.part_number());

  EXPECT_TRUE(res == details);
}

TEST_F(DetailsFacadeTests, remove_swap) {
  Detail detail_src = detail_mother_object_.create_detail();
  Detail detail_dst = detail_mother_object_.create_detail();

  EXPECT_CALL(*swaps_db_,
              delete_(detail_src.part_number(), detail_dst.part_number()))
      .Times(1);

  DetailsFacade::instanse().delete_detail_swap(detail_src.part_number(),
                                               detail_dst.part_number());
}

TEST_F(DetailsFacadeTests, add_to_stock) {
  StockLog stock_log = StockLogDataBuilder()
                           .with_fk_worker(1)
                           ->with_fk_detail("test")
                           ->with_change(2)
                           ->build();
  EXPECT_CALL(*stock_db_, create(stock_log.fk_detail(), stock_log.fk_worker(),
                                 stock_log.change()))
      .Times(1);

  DetailsFacade::instanse().add_detail_to_stock(
      stock_log.fk_detail(), stock_log.fk_worker(), stock_log.change());
}

TEST_F(DetailsFacadeTests, remove_from_stock) {
  StockLog stock_log = StockLogDataBuilder()
                           .with_fk_worker(1)
                           ->with_fk_detail("test")
                           ->with_change(2)
                           ->build();

  EXPECT_CALL(*stock_db_, delete_(stock_log.fk_detail(), stock_log.fk_worker(),
                                  stock_log.change()))
      .Times(1);

  DetailsFacade::instanse().remove_detail_from_stock(
      stock_log.fk_detail(), stock_log.fk_worker(), stock_log.change());
}

TEST_F(DetailsFacadeTests, stock_info) {
  StockLog stock_log =
      StockLogDataBuilder().with_fk_detail("test")->with_change(2)->build();
  detail_quantity_t quantity(stock_log.fk_detail(), stock_log.change());

  EXPECT_CALL(*stock_db_, read(stock_log.fk_detail()))
      .Times(1)
      .WillRepeatedly(Return(quantity));

  detail_quantity_t res =
      DetailsFacade::instanse().get_detail_in_stock(stock_log.fk_detail());
  EXPECT_TRUE(quantity == res);
}

TEST_F(DetailsFacadeTests, stock_prev_details) {
  details_t details = detail_mother_object_.create_details();
  details_names_t names(details.size());
  std::transform(details.data(), details.data() + details.size(), names.data(),
                 [](const Detail& d) { return d.part_number(); });

  EXPECT_CALL(*stock_db_, read_prev()).Times(1).WillRepeatedly(Return(names));

  details_names_t res = DetailsFacade::instanse().get_prev_details_in_stock();
  EXPECT_TRUE(names == res);
}

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
