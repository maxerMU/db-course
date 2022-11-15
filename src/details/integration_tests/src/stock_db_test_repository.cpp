#include "stock_db_test_repository.h"
#include "base_sections.h"
#include "database_exceptions.h"
#include "yamlcpp_config.h"

StockDbTest::StockDbTest(const std::shared_ptr<BaseConfig>& conf,
                         const std::string& connection_section) {
  read_config(conf, connection_section);
  connect();
  add_prepare_statements();
}

void StockDbTest::read_config(const std::shared_ptr<BaseConfig>& conf,
                              const std::string& connection_section) {
  name_ = conf->get_string_field({connection_section, DbNameSection});
  user_ = conf->get_string_field({connection_section, DbUserSection});
  user_password_ =
      conf->get_string_field({connection_section, DbUserPasswordSection});
  host_ = conf->get_string_field({connection_section, DbHostSection});
  port_ = conf->get_uint_field({connection_section, DbPortSection});
}

void StockDbTest::connect() {
  std::string connection_string = "dbname = " + name_ + " user = " + user_ +
                                  " password = " + user_password_ +
                                  " host = " + host_ +
                                  " port = " + std::to_string(port_);

  try {
    connection_ = std::shared_ptr<pqxx::connection>(
        new pqxx::connection(connection_string.c_str()));

    if (!connection_->is_open()) {
      throw DatabaseConnectException("can't connect to " + name_);
    }

  } catch (std::exception& ex) {
    throw DatabaseConnectException("can't connect to " + name_ + " " +
                                   ex.what());
  }
}

void StockDbTest::add_prepare_statements() {
  connection_->prepare(requests_names[CREATE],
                       "CALL PR_ADD_DETAIL($1, $2, $3, $4)");
  connection_->prepare(requests_names[READ_BY_ID],
                       "SELECT * FROM FN_GET_DETAIL_BY_ID($1)");
  connection_->prepare(requests_names[DELETE], "CALL PR_DELETE_DETAIL($1)");
  connection_->prepare(requests_names[CREATE_PRODUCER],
                       "SELECT FN_ADD_PRODUCER($1, $2)");
  connection_->prepare(requests_names[READ_PRODUCER],
                       "SELECT * FROM FN_GET_PRODUCER_BY_ID($1)");
  connection_->prepare(requests_names[CREATE_SWAP], "CALL PR_ADD_SWAP($1, $2)");
  connection_->prepare(requests_names[READ_SWAP],
                       "SELECT * FROM FN_GET_SWAPS($1)");
  connection_->prepare(requests_names[UPDATE_LOG],
                       "CALL PR_UPDATE_STOCK($1, $2, $3)");
  connection_->prepare(requests_names[READ_LOG],
                       "SELECT FN_GET_DETAIL_QUANTITY($1)");
  connection_->prepare(requests_names[CREATE_WORKER],
                       "SELECT * FROM FN_ADD_WORKER($1, $2, $3, $4, $5, $6)");
  connection_->prepare(requests_names[CLEAN], "CALL PR_CLEAN_DATABASE()");
}

void StockDbTest::create(const Detail& detail) {
  try {
    pqxx::work w(*connection_);
    w.exec_prepared(requests_names[CREATE], detail.part_number(),
                    detail.name_rus(), detail.name_eng(), detail.producer_id());
    w.commit();
  } catch (...) {
    throw DatabaseExecutionException("can't execute prepared");
  }
}

Detail StockDbTest::read(const std::string& part_name) {
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

void StockDbTest::delete_(const std::string& part_name) {
  try {
    pqxx::work w(*connection_);
    w.exec_prepared(requests_names[DELETE], part_name);
    w.commit();
  } catch (...) {
    throw DatabaseExecutionException("can't execute prepared");
  }
}

size_t StockDbTest::create_producer(const DetailsProducerData& producer) {
  try {
    pqxx::work w(*connection_);
    pqxx::result res = w.exec_prepared(requests_names[CREATE_PRODUCER],
                                       producer.name(), producer.country());
    w.commit();

    return res[0][0].as<size_t>();
  } catch (...) {
    throw DatabaseExecutionException("can't execute prepared");
  }
}

DetailsProducer StockDbTest::read_producer(size_t producer_id) {
  pqxx::result res;
  try {
    pqxx::work w(*connection_);
    res = w.exec_prepared(requests_names[READ_PRODUCER], producer_id);
    w.commit();
  } catch (...) {
    throw DatabaseExecutionException("can't execute prepared");
  }

  if (res.size() == 0)
    throw DatabaseNotFoundException("Can't find producer");

  DetailsProducer producer;
  producer = DetailsProducer(res[0]["id"].as<size_t>(),
                             res[0]["name"].as<std::string>(),
                             res[0]["country"].as<std::string>());

  return producer;
}

void StockDbTest::create_swap(const std::string& src, const std::string& dst) {
  try {
    pqxx::work w(*connection_);
    w.exec_prepared(requests_names[CREATE_SWAP], src, dst);
    w.commit();
  } catch (...) {
    throw DatabaseExecutionException("can't execute prepared");
  }
}

details_names_t StockDbTest::read_swap(const std::string& src) {
  pqxx::result res;
  try {
    pqxx::work w(*connection_);
    res = w.exec_prepared(requests_names[READ_SWAP], src);
    w.commit();
  } catch (...) {
    throw DatabaseExecutionException("can't execute prepared");
  }

  std::vector<std::string> part_names;
  for (auto const& row : res) {
    part_names.push_back(row["part_name"].as<std::string>());
  }

  return part_names;
}

void StockDbTest::create_log(const std::string& part_name,
                             size_t worker_id,
                             size_t quantity) {
  try {
    pqxx::work w(*connection_);
    w.exec_prepared(requests_names[UPDATE_LOG], part_name, worker_id, quantity);
    w.commit();
  } catch (std::exception& ex) {
    throw DatabaseExecutionException(ex.what());
  }
}

detail_quantity_t StockDbTest::read_log(const std::string& part_name) {
  pqxx::result res;
  try {
    pqxx::work w(*connection_);
    res = w.exec_prepared(requests_names[READ_LOG], part_name);
    w.commit();
  } catch (...) {
    throw DatabaseExecutionException("can't execute prepared");
  }

  if (res.size() == 0)
    throw DatabaseIncorrectAnswerException("no answer from database");

  return detail_quantity_t(part_name, res[0][0].as<size_t>());
}

void StockDbTest::delete_log(const std::string& part_name,
                             size_t worker_id,
                             size_t quantity) {
  try {
    pqxx::work w(*connection_);
    long long change = quantity;
    w.exec_prepared(requests_names[UPDATE_LOG], part_name, worker_id, -change);
    w.commit();
  } catch (std::exception& ex) {
    throw DatabaseExecutionException(ex.what());
  }
}

size_t StockDbTest::create_test_worker() {
  pqxx::work w(*connection_);
  std::string birthdate = "2002-04-03";
  pqxx::result res =
      w.exec_prepared(requests_names[CREATE_WORKER], std::string(),
                      std::string(), birthdate, 1, "test", std::string());
  w.commit();

  return res[0][1].as<size_t>();
}

void StockDbTest::clean_database() {
  // try {
  pqxx::work w(*connection_);
  w.exec_prepared(requests_names[CLEAN]);
  w.commit();
  // } catch (...) {
  //  throw DatabaseExecutionException("can't execute prepared");
  // }
}
