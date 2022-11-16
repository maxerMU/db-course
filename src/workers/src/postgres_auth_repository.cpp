#include "postgres_auth_repository.h"
#include "base_sections.h"
#include "database_exceptions.h"
#include "iostream"

PostgresAuthRepository::PostgresAuthRepository(
    const std::shared_ptr<BaseConfig>& conf,
    const std::string& connection_section) {
  read_config(conf, connection_section);
  connect();
  add_prepare_statements();
}

void PostgresAuthRepository::read_config(
    const std::shared_ptr<BaseConfig>& conf,
    const std::string& connection_section) {
  name_ = conf->get_string_field({connection_section, DbNameSection});
  user_ = conf->get_string_field({connection_section, DbUserSection});
  user_password_ =
      conf->get_string_field({connection_section, DbUserPasswordSection});
  host_ = conf->get_string_field({connection_section, DbHostSection});
  port_ = conf->get_uint_field({connection_section, DbPortSection});
}

void PostgresAuthRepository::connect() {
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

void PostgresAuthRepository::add_prepare_statements() {
  connection_->prepare(requests_names[CREATE], "CALL PR_ADD_SESSION($1, $2)");
  connection_->prepare(requests_names[IS_VALID],
                       "SELECT * FROM FN_GET_SESSION_DATA($1)");
}

void PostgresAuthRepository::create_session(size_t worker_id,
                                            const std::string& token) {
  pqxx::work w(*connection_);
  w.exec_prepared(requests_names[CREATE], worker_id, token);
  w.commit();
}

bool PostgresAuthRepository::is_valid_session(size_t& worker_id,
                                              const std::string& token) {
  pqxx::work w(*connection_);
  pqxx::result res = w.exec_prepared(requests_names[IS_VALID], token);
  w.commit();

  bool is_valid = res[0][0].as<bool>();
  if (is_valid)
    worker_id = res[0][1].as<size_t>();

  return is_valid;
}
