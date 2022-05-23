#include "details_repository_test.h"
#include "base_sections.h"
#include "database_exceptions.h"
#include "yamlcpp_config.h"

PostgresDetailsTestRepository::PostgresDetailsTestRepository(
    const std::shared_ptr<BaseConfig>& conf,
    const std::string& connection_section) {
  read_config(conf, connection_section);
  connect();
  add_prepare_statements();
}

void PostgresDetailsTestRepository::read_config(
    const std::shared_ptr<BaseConfig>& conf,
    const std::string& connection_section) {
  name_ = conf->get_string_field({connection_section, DbNameSection});
  user_ = conf->get_string_field({connection_section, DbUserSection});
  user_password_ =
      conf->get_string_field({connection_section, DbUserPasswordSection});
  host_ = conf->get_string_field({connection_section, DbHostSection});
  port_ = conf->get_uint_field({connection_section, DbPortSection});
}

void PostgresDetailsTestRepository::connect() {
  std::string connection_string = "dbname = " + name_ + " user = " + user_ +
                                  " password = " + user_password_ +
                                  " hostaddr = " + host_ +
                                  " port = " + std::to_string(port_);

  try {
    connection_ = std::shared_ptr<pqxx::connection>(
        new pqxx::connection(connection_string.c_str()));

    if (!connection_->is_open()) {
      throw DatabaseConnectException("can't connect to " + name_);
    } else
      std::cout << "Connected to db " << name_ << std::endl;

  } catch (std::exception& ex) {
    throw DatabaseConnectException("can't connect to " + name_ + " " +
                                   ex.what());
  }
}

void PostgresDetailsTestRepository::add_prepare_statements() {
  connection_->prepare(requests_names[CREATE],
                       "CALL PR_ADD_DETAIL($1, $2, $3, $4)");
  connection_->prepare(requests_names[READ_BY_ID],
                       "SELECT * FROM FN_GET_DETAIL_BY_ID($1)");
  connection_->prepare(requests_names[DELETE], "CALL PR_DELETE_DETAIL($1)");
}

void PostgresDetailsTestRepository::create(const Detail& detail) {
  try {
    pqxx::work w(*connection_);
    w.exec_prepared(requests_names[CREATE], detail.part_number(),
                    detail.name_rus(), detail.name_eng(), detail.producer_id());
    w.commit();
  } catch (...) {
    throw DatabaseExecutionException("can't execute prepared");
  }
}

Detail PostgresDetailsTestRepository::read(const std::string& part_name) {
  pqxx::result res;
  try {
    pqxx::work w(*connection_);
    res = w.exec_prepared(requests_names[READ_BY_ID], part_name);
    w.commit();
  } catch (...) {
    throw DatabaseExecutionException("can't execute prepared");
  }

  if (res.size() == 0)
    throw DatabaseNotFoundException("no detail");

  auto row = res[0];
  auto detail = Detail(
      row["name_rus"].as<std::string>(), row["name_eng"].as<std::string>(),
      row["part_name"].as<std::string>(), row["producer_id"].as<size_t>());

  return detail;
}

void PostgresDetailsTestRepository::delete_(const std::string& part_name) {
  try {
    pqxx::work w(*connection_);
    w.exec_prepared(requests_names[DELETE], part_name);
    w.commit();
  } catch (...) {
    throw DatabaseExecutionException("can't execute prepared");
  }
}

void DetailsRepositoryTest::SetUp() {
  std::shared_ptr<BaseConfig> config(new YamlCppConfig(ConfFileName));
  test_rep = std::shared_ptr<PostgresDetailsTestRepository>(
      new PostgresDetailsTestRepository(config, ConfDetialsDbSection));

  details_rep = std::shared_ptr<PostgresDetailsRepository>(
      new PostgresDetailsRepository(config, ConfDetialsDbSection));
}

void DetailsRepositoryTest::TearDown() {}

TEST_F(DetailsRepositoryTest, create_detail) {
  Detail detail("test", "test", "test", 1);
  details_rep->create(detail);

  auto read_detail = test_rep->read("test");
  test_rep->delete_("test");

  ASSERT_TRUE(detail == read_detail);
}

TEST_F(DetailsRepositoryTest, read_detail) {
  Detail detail("test", "test", "test", 1);
  test_rep->create(detail);

  auto read_detail = details_rep->read("test");
  test_rep->delete_("test");

  ASSERT_TRUE(detail == read_detail);
}

TEST_F(DetailsRepositoryTest, update_detail) {
  Detail detail("test", "test", "test", 1);
  test_rep->create(detail);
  detail.set_producer_id(2);

  details_rep->update(detail);
  auto read_detail = test_rep->read("test");
  test_rep->delete_("test");

  ASSERT_TRUE(detail == read_detail);
}

TEST_F(DetailsRepositoryTest, delete_detail) {
  Detail detail("test", "test", "test", 1);
  test_rep->create(detail);

  details_rep->delete_("test");
  EXPECT_THROW(test_rep->read("test"), DatabaseNotFoundException);
}
