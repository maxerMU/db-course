#include "postgres_stock_repository.h"
#include "base_sections.h"
#include "database_exceptions.h"
#include "iostream"

PostgresStockRepository::PostgresStockRepository(
    const std::shared_ptr<BaseConfig>& conf,
    const std::string& connection_section) {
  read_config(conf, connection_section);
  connect();
  add_prepare_statements();
}

void PostgresStockRepository::read_config(
    const std::shared_ptr<BaseConfig>& conf,
    const std::string& connection_section) {
  name_ = conf->get_string_field({connection_section, DbNameSection});
  user_ = conf->get_string_field({connection_section, DbUserSection});
  user_password_ =
      conf->get_string_field({connection_section, DbUserPasswordSection});
  host_ = conf->get_string_field({connection_section, DbHostSection});
  port_ = conf->get_uint_field({connection_section, DbPortSection});
}

void PostgresStockRepository::connect() {
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

void PostgresStockRepository::add_prepare_statements() {
  connection_->prepare(requests_names[UPDATE],
                       "CALL PR_UPDATE_STOCK($1, $2, $3)");
  connection_->prepare(requests_names[READ_BY_ID],
                       "SELECT FN_GET_DETAIL_QUANTITY($1)");
  connection_->prepare(requests_names[READ_CURR],
                       "SELECT * FROM FN_STOCK_CURRENT_DETAILS()");
  connection_->prepare(requests_names[READ_PREV],
                       "SELECT * FROM FN_STOCK_PREVIOUS_DETAILS()");
}

void PostgresStockRepository::create(const std::string& part_name,
                                     size_t worker_id,
                                     size_t quantity) {
  try {
    pqxx::work w(*connection_);
    w.exec_prepared(requests_names[UPDATE], part_name, worker_id, quantity);
    w.commit();
  } catch (...) {
    throw DatabaseExecutionException("can't execute prepared");
  }
}

detail_quantity_t PostgresStockRepository::read(const std::string& part_name) {
  pqxx::result res;
  try {
    pqxx::work w(*connection_);
    res = w.exec_prepared(requests_names[READ_BY_ID], part_name);
    w.commit();
  } catch (...) {
    throw DatabaseExecutionException("can't execute prepared");
  }

  if (res.size() == 0)
    throw DatabaseIncorrectAnswerException("no answer from database");

  return detail_quantity_t(part_name, res[0][0].as<size_t>());
}

details_quantities_t PostgresStockRepository::read_current() {
  pqxx::result res;
  try {
    pqxx::work w(*connection_);
    res = w.exec_prepared(requests_names[READ_CURR]);
    w.commit();
  } catch (...) {
    throw DatabaseExecutionException("can't execute prepared");
  }

  details_quantities_t details_quantities;
  for (auto const& row : res) {
    details_quantities.push_back(detail_quantity_t(
        row["part_number"].as<std::string>(), row["quantity"].as<size_t>()));
  }

  return details_quantities;
}

details_names_t PostgresStockRepository::read_prev() {
  pqxx::result res;
  try {
    pqxx::work w(*connection_);
    res = w.exec_prepared(requests_names[READ_PREV]);
    w.commit();
  } catch (...) {
    throw DatabaseExecutionException("can't execute prepared");
  }

  details_names_t part_numbers;
  for (auto const& row : res) {
    part_numbers.push_back(row["part_number"].as<std::string>());
  }

  return part_numbers;
}

void PostgresStockRepository::delete_(const std::string& part_name,
                                      size_t worker_id,
                                      size_t quantity) {
  try {
    pqxx::work w(*connection_);
    long long quantity_int = quantity;
    w.exec_prepared(requests_names[UPDATE], part_name, worker_id,
                    -quantity_int);
    w.commit();
  } catch (...) {
    throw DatabaseExecutionException("can't execute prepared");
  }
}
