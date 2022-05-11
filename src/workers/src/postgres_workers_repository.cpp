#include "postgres_workers_repository.h"
#include "base_sections.h"
#include "database_exceptions.h"
#include "iostream"

PostgresWorkersRepository::PostgresWorkersRepository(
    const std::shared_ptr<BaseConfig>& conf,
    const std::string& connection_section) {
  read_config(conf, connection_section);
  connect();
  add_prepare_statements();
}

void PostgresWorkersRepository::read_config(
    const std::shared_ptr<BaseConfig>& conf,
    const std::string& connection_section) {
  name_ = conf->get_string_field({connection_section, DbNameSection});
  user_ = conf->get_string_field({connection_section, DbUserSection});
  user_password_ =
      conf->get_string_field({connection_section, DbUserPasswordSection});
  host_ = conf->get_string_field({connection_section, DbHostSection});
  port_ = conf->get_uint_field({connection_section, DbPortSection});
}

void PostgresWorkersRepository::connect() {
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

void PostgresWorkersRepository::add_prepare_statements() {
  connection_->prepare(requests_names[CREATE],
                       "SELECT FN_ADD_WORKER($1, $2, $3, $4, $5, $6)");
  connection_->prepare(requests_names[READ_COUNT], "SELECT FN_WORKERS_COUNT()");
  connection_->prepare(requests_names[READ_PASSWORD],
                       "SELECT * FROM FN_GET_PASSWORD($1)");
}

int PostgresWorkersRepository::create(const WorkerPost& worker) {
  pqxx::work w(*connection_);
  std::string birthdate = std::to_string(worker.birthdate().tm_year + 1900) +
                          "-" + std::to_string(worker.birthdate().tm_mon + 1) +
                          "-" + std::to_string(worker.birthdate().tm_mday);
  pqxx::result res = w.exec_prepared(
      requests_names[CREATE], worker.name(), worker.surname(), birthdate,
      (int)worker.getPrivilege(), worker.username(), worker.password());
  w.commit();

  return res[0][0].as<size_t>();
}

size_t PostgresWorkersRepository::workers_count() {
  pqxx::work w(*connection_);
  pqxx::result res = w.exec_prepared(requests_names[READ_COUNT]);
  w.commit();

  return res[0][0].as<size_t>();
}

void PostgresWorkersRepository::update(const WorkerUpdate& worker) {}

bool PostgresWorkersRepository::get_password(std::string& password,
                                             size_t& worker_id,
                                             const std::string& username) {
  pqxx::work w(*connection_);
  pqxx::result res = w.exec_prepared(requests_names[READ_PASSWORD], username);
  w.commit();

  if (!res[0][0].as<bool>())
    return false;

  worker_id = res[0][1].as<size_t>();
  password = res[0][2].as<std::string>();

  return true;
}
