#include "postgres_swaps_repository.h"
#include <iostream>
#include "base_sections.h"
#include "database_exceptions.h"

PostgresSwapsRepository::PostgresSwapsRepository(
    const std::shared_ptr<BaseConfig>& conf,
    const std::string& connection_section) {
  read_config(conf, connection_section);
  connect();
  add_prepare_statements();
}

void PostgresSwapsRepository::read_config(
    const std::shared_ptr<BaseConfig>& conf,
    const std::string& connection_section) {
  name_ = conf->get_string_field({connection_section, DbNameSection});
  user_ = conf->get_string_field({connection_section, DbUserSection});
  user_password_ =
      conf->get_string_field({connection_section, DbUserPasswordSection});
  host_ = conf->get_string_field({connection_section, DbHostSection});
  port_ = conf->get_uint_field({connection_section, DbPortSection});
}

void PostgresSwapsRepository::connect() {
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

void PostgresSwapsRepository::add_prepare_statements() {
  connection_->prepare(requests_names[CREATE], "CALL PR_ADD_SWAP($1, $2)");
  connection_->prepare(requests_names[READ], "SELECT * FROM FN_GET_SWAPS($1)");
  connection_->prepare(requests_names[DELETE], "CALL PR_DELETE_SWAP($1, $2)");
}

void PostgresSwapsRepository::create(const std::string& src,
                                     const std::string& dst) {
  try {
    pqxx::work w(*connection_);
    w.exec_prepared(requests_names[CREATE], src, dst);
    w.commit();
  } catch (...) {
    throw DatabaseExecutionException("can't execute prepared");
  }
}

std::vector<std::string> PostgresSwapsRepository::read(const std::string& src) {
  pqxx::result res;
  try {
    pqxx::work w(*connection_);
    res = w.exec_prepared(requests_names[READ], src);
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

void PostgresSwapsRepository::delete_(const std::string& src,
                                      const std::string& dst) {
  try {
    pqxx::work w(*connection_);
    w.exec_prepared(requests_names[DELETE], src, dst);
    w.commit();
  } catch (...) {
    throw DatabaseExecutionException("can't execute prepared");
  }
}
