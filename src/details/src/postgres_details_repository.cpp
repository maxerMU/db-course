#include "postgres_details_repository.h"
#include <iostream>
#include "base_sections.h"
#include "database_exceptions.h"

PostgresDetailsRepository::PostgresDetailsRepository(
    const std::shared_ptr<BaseConfig>& conf,
    const std::string& connection_section) {
  read_config(conf, connection_section);
  connect();
  add_prepare_statements();
}

void PostgresDetailsRepository::read_config(
    const std::shared_ptr<BaseConfig>& conf,
    const std::string& connection_section) {
  name_ = conf->get_string_field({connection_section, DbNameSection});
  user_ = conf->get_string_field({connection_section, DbUserSection});
  user_password_ =
      conf->get_string_field({connection_section, DbUserPasswordSection});
  host_ = conf->get_string_field({connection_section, DbHostSection});
  port_ = conf->get_uint_field({connection_section, DbPortSection});
}

void PostgresDetailsRepository::connect() {
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

void PostgresDetailsRepository::add_prepare_statements() {
  connection_->prepare(requests_names[CREATE],
                       "CALL PR_ADD_DETAIL($1, $2, $3, $4)");
  connection_->prepare(requests_names[READ_ALL],
                       "SELECT * FROM FN_GET_ALL_DETAILS()");
  connection_->prepare(requests_names[READ_BY_ID],
                       "SELECT * FROM FN_GET_DETAIL_BY_ID($1)");
  connection_->prepare(requests_names[UPDATE],
                       "CALL PR_UPDATE_DETAIL($1, $2, $3, $4)");
  connection_->prepare(requests_names[DELETE], "CALL PR_DELETE_DETAIL($1)");
}

void PostgresDetailsRepository::create(const Detail& detail) {
  pqxx::work w(*connection_);
  w.exec_prepared(requests_names[CREATE], detail.part_number(),
                  detail.name_rus(), detail.name_eng(), detail.producer_id());
  w.commit();
}

Detail PostgresDetailsRepository::read(const std::string& part_name) {
  pqxx::work w(*connection_);
  pqxx::result res = w.exec_prepared(requests_names[READ_BY_ID], part_name);
  w.commit();

  auto row = res[0];
  auto detail = Detail(
      row["name_rus"].as<std::string>(), row["name_eng"].as<std::string>(),
      row["part_name"].as<std::string>(), row["producer_id"].as<size_t>());

  return detail;
}

details_t PostgresDetailsRepository::read_all() {
  pqxx::work w(*connection_);
  pqxx::result res = w.exec_prepared(requests_names[READ_ALL]);
  w.commit();

  details_t details;
  for (auto const& row : res) {
    details.push_back(Detail(
        row["name_rus"].as<std::string>(), row["name_eng"].as<std::string>(),
        row["part_name"].as<std::string>(), row["producer_id"].as<size_t>()));
  }

  return details;
}

void PostgresDetailsRepository::update(const Detail& detail) {
  pqxx::work w(*connection_);
  w.exec_prepared(requests_names[UPDATE], detail.part_number(),
                  detail.name_rus(), detail.name_eng(), detail.producer_id());
  w.commit();
}

void PostgresDetailsRepository::delete_(const std::string& part_name) {
  pqxx::work w(*connection_);
  w.exec_prepared(requests_names[DELETE], part_name);
  w.commit();
}
