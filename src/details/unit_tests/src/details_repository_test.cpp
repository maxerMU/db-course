// #include "details_repository_test.h"
// #include "database_exceptions.h"
// #include "yamlcpp_config.h"
//
// DetailsRepositoryTest::DetailsRepositoryTest() {
//   std::shared_ptr<BaseConfig> config(new YamlCppConfig(ConfFileName));
//   test_rep =
//       std::shared_ptr<StockDbTest>(new StockDbTest(config,
//       ConfStockDbSection));
//
//   details_rep = std::shared_ptr<PostgresDetailsRepository>(
//       new PostgresDetailsRepository(config, ConfDetialsDbSection));
// }
//
// void DetailsRepositoryTest::SetUp() {
//   test_rep->clean_database();
// }
//
// void DetailsRepositoryTest::TearDown() {
//   test_rep->clean_database();
// }
//
// TEST_F(DetailsRepositoryTest, create_detail) {
//   DetailsProducerData producer =
//   producer_mother_object_.create_producer_data(); size_t producer_id =
//   test_rep->create_producer(producer); Detail detail =
//   detail_mother_object_.create_detail(); detail.set_producer_id(producer_id);
//
//   details_rep->create(detail);
//
//   auto read_detail = test_rep->read(detail.part_number());
//   ASSERT_TRUE(detail == read_detail);
// }
//
// TEST_F(DetailsRepositoryTest, read_detail) {
//   DetailsProducerData producer =
//   producer_mother_object_.create_producer_data(); size_t producer_id =
//   test_rep->create_producer(producer); Detail detail =
//   detail_mother_object_.create_detail(); detail.set_producer_id(producer_id);
//   test_rep->create(detail);
//
//   auto read_detail = details_rep->read(detail.part_number());
//
//   ASSERT_TRUE(detail == read_detail);
// }
//
// TEST_F(DetailsRepositoryTest, update_detail) {
//   DetailsProducerData producer =
//   producer_mother_object_.create_producer_data(); size_t producer_id =
//   test_rep->create_producer(producer); Detail detail =
//   detail_mother_object_.create_detail(); detail.set_producer_id(producer_id);
//   test_rep->create(detail);
//   detail.set_name_rus(detail.name_rus() + detail.name_eng());
//
//   details_rep->update(detail);
//
//   auto read_detail = test_rep->read(detail.part_number());
//   ASSERT_TRUE(detail == read_detail);
// }
//
// TEST_F(DetailsRepositoryTest, delete_detail) {
//   DetailsProducerData producer =
//   producer_mother_object_.create_producer_data(); size_t producer_id =
//   test_rep->create_producer(producer); Detail detail =
//   detail_mother_object_.create_detail(); detail.set_producer_id(producer_id);
//   test_rep->create(detail);
//
//   details_rep->delete_(detail.part_number());
//
//   EXPECT_THROW(test_rep->read(detail.part_number()),
//   DatabaseNotFoundException);
// }
