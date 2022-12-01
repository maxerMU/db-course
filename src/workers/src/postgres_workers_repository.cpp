#include "postgres_workers_repository.h"
#include <time.h>
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
                                  " host = " + host_ +
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
                       "SELECT * FROM FN_ADD_WORKER($1, $2, $3, $4, $5, $6)");
  connection_->prepare(requests_names[READ], "SELECT * FROM FN_GET_WORKERS()");
  connection_->prepare(requests_names[READ_COUNT], "SELECT FN_WORKERS_COUNT()");
  connection_->prepare(requests_names[READ_PASSWORD],
                       "SELECT * FROM FN_GET_PASSWORD($1)");
  connection_->prepare(requests_names[READ_BASE_INF],
                       "SELECT * FROM FN_GET_WORKER_BY_ID($1)");
  connection_->prepare(
      requests_names[UPDATE],
      "SELECT * FROM FN_UPDATE_WORKER($1, $2, $3, $4, $5, $6)");
  connection_->prepare(requests_names[UPDATE_PRIVILEGE],
                       "CALL PR_UPDATE_WORKER_PRIVILEGE($1, $2)");
}

size_t PostgresWorkersRepository::create(const WorkerPost& worker) {
  pqxx::work w(*connection_);
  std::string birthdate = std::to_string(worker.birthdate().tm_year + 1900) +
                          "-" + std::to_string(worker.birthdate().tm_mon + 1) +
                          "-" + std::to_string(worker.birthdate().tm_mday);
  pqxx::result res = w.exec_prepared(
      requests_names[CREATE], worker.name(), worker.surname(), birthdate,
      (int)worker.getPrivilege(), worker.username(), worker.password());
  w.commit();

  if (res[0][0].as<size_t>() != 0)
    throw DatabaseNotUniqueUsernameException();

  return res[0][1].as<size_t>();
}

std::vector<WorkerGet> PostgresWorkersRepository::read() {
  pqxx::work w(*connection_);
  pqxx::result res = w.exec_prepared(requests_names[READ]);
  w.commit();

  if (res.size() == 0)
    throw DatabaseNotFoundException("can't find user");

  std::vector<WorkerGet> workers;

  for (auto row : res) {
    WorkerGet worker;

    worker.setWorkerId(row[0].as<int>());
    worker.setName(row[1].as<std::string>());
    worker.setSurname(row[2].as<std::string>());

    auto birthdate_str = row[3].as<std::string>();
    tm birthdate;
    if (!strptime(birthdate_str.c_str(), "%Y-%m-%d", &birthdate))
      throw DatabaseIncorrectAnswerException("can't parse datetime");

    worker.setBirthdate(birthdate);
    worker.setPrivilege(static_cast<PrivilegeLevel>(row[4].as<int>()));

    workers.push_back(worker);
  }

  return workers;
}

size_t PostgresWorkersRepository::workers_count() {
  pqxx::work w(*connection_);
  pqxx::result res = w.exec_prepared(requests_names[READ_COUNT]);
  w.commit();

  return res[0][0].as<size_t>();
}

WorkerBaseInf PostgresWorkersRepository::read(size_t worker_id) {
  pqxx::work w(*connection_);
  pqxx::result res = w.exec_prepared(requests_names[READ_BASE_INF], worker_id);
  w.commit();

  if (res.size() == 0)
    throw DatabaseNotFoundException("can't find user");

  WorkerBaseInf worker;

  worker.setName(res[0][0].as<std::string>());
  worker.setSurname(res[0][1].as<std::string>());

  auto birthdate_str = res[0][2].as<std::string>();
  tm birthdate;
  if (!strptime(birthdate_str.c_str(), "%Y-%m-%d", &birthdate))
    throw DatabaseIncorrectAnswerException("can't parse datetime");

  worker.setBirthdate(birthdate);
  worker.setPrivilege(static_cast<PrivilegeLevel>(res[0][3].as<int>()));

  return worker;
}

int PostgresWorkersRepository::update(const WorkerUpdate& worker) {
  pqxx::work w(*connection_);
  std::string birthdate = std::to_string(worker.birthdate().tm_year + 1900) +
                          "-" + std::to_string(worker.birthdate().tm_mon + 1) +
                          "-" + std::to_string(worker.birthdate().tm_mday);
  pqxx::result res = w.exec_prepared(
      requests_names[UPDATE], worker.getWorker_id(), worker.name(),
      worker.surname(), birthdate, worker.username(), worker.password());
  w.commit();

  return res[0][0].as<size_t>();
}

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

void PostgresWorkersRepository::update_privilege(
    size_t worker_id,
    const PrivilegeLevel& privilege) {
  pqxx::work w(*connection_);
  w.exec_prepared(requests_names[UPDATE_PRIVILEGE], worker_id, (int)privilege);
  w.commit();
}
