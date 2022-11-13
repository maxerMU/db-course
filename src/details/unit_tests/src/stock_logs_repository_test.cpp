// #include "stock_logs_repository_test.h"
// #include <ctime>
// #include "database_exceptions.h"
// #include "yamlcpp_config.h"
//
// StockRepositoryTest::StockRepositoryTest() : worker_id_(0) {
//   std::shared_ptr<BaseConfig> config(new YamlCppConfig(ConfFileName));
//   test_rep =
//       std::shared_ptr<StockDbTest>(new StockDbTest(config,
//       ConfStockDbSection));
//
//   logs_rep = std::shared_ptr<PostgresStockRepository>(
//       new PostgresStockRepository(config, ConfStockLogDbSection));
// }
//
// void StockRepositoryTest::SetUp() {
//   test_rep->clean_database();
//
//   details_ = detail_mother_object.create_details();
//
//   for (auto& detail : details_) {
//     DetailsProducerData producer =
//         producer_mother_object.create_producer_data();
//
//     size_t producer_id = test_rep->create_producer(producer);
//     detail.set_producer_id(producer_id);
//     test_rep->create(detail);
//   }
//
//   worker_id_ = test_rep->create_test_worker();
// }
//
// void StockRepositoryTest::TearDown() {
//   test_rep->clean_database();
// }
//
// TEST_F(StockRepositoryTest, create_log) {
//   size_t change = 5;
//   StockLog log =
//       stock_log_data_builder.with_fk_detail(details_[0].part_number())
//           ->with_fk_worker(worker_id_)
//           ->with_change(change)
//           ->build();
//
//   logs_rep->create(log.fk_detail(), log.fk_worker(), log.change());
//
//   detail_quantity_t detail_quantity = test_rep->read_log(log.fk_detail());
//   ASSERT_EQ(detail_quantity.first, log.fk_detail());
//   ASSERT_EQ(detail_quantity.second, change);
// }
//
// TEST_F(StockRepositoryTest, delete_log) {
//   size_t change_insert = 5;
//   size_t change_delete = 2;
//   StockLog log_insert =
//       stock_log_data_builder.with_fk_detail(details_[0].part_number())
//           ->with_fk_worker(worker_id_)
//           ->with_change(change_insert)
//           ->build();
//   StockLog log_delete =
//       stock_log_data_builder.with_fk_detail(details_[0].part_number())
//           ->with_fk_worker(worker_id_)
//           ->with_change(change_delete)
//           ->build();
//   test_rep->create_log(log_insert.fk_detail(), log_insert.fk_worker(),
//                        log_insert.change());
//
//   logs_rep->delete_(log_delete.fk_detail(), log_delete.fk_worker(),
//                     log_delete.change());
//
//   detail_quantity_t detail_quantity =
//       test_rep->read_log(log_insert.fk_detail());
//   ASSERT_EQ(detail_quantity.first, log_insert.fk_detail());
//   ASSERT_EQ(detail_quantity.second, change_insert - change_delete);
// }
//
// TEST_F(StockRepositoryTest, read_current) {
//   size_t change = 5;
//   std::vector<StockLog> logs;
//   for (auto detail : details_) {
//     StockLog log =
//     stock_log_data_builder.with_fk_detail(detail.part_number())
//                        ->with_fk_worker(worker_id_)
//                        ->with_change(change)
//                        ->build();
//     logs.push_back(log);
//     test_rep->create_log(log.fk_detail(), log.fk_worker(), log.change());
//   }
//
//   details_quantities_t quantities = logs_rep->read_current();
//
//   for (size_t i = 0; i < logs.size(); i++) {
//     ASSERT_EQ(quantities[i].first, logs[i].fk_detail());
//     ASSERT_EQ(quantities[i].second, change);
//   }
// }
//
// TEST_F(StockRepositoryTest, read_prev) {
//   size_t change = 5;
//   std::vector<StockLog> logs;
//   for (auto detail : details_) {
//     StockLog log =
//     stock_log_data_builder.with_fk_detail(detail.part_number())
//                        ->with_fk_worker(worker_id_)
//                        ->with_change(change)
//                        ->build();
//     logs.push_back(log);
//     test_rep->create_log(log.fk_detail(), log.fk_worker(), log.change());
//     test_rep->delete_log(log.fk_detail(), log.fk_worker(), log.change());
//   }
//
//   details_names_t names = logs_rep->read_prev();
//
//   for (size_t i = 0; i < logs.size(); i++) {
//     ASSERT_EQ(names[i], logs[i].fk_detail());
//   }
// }
