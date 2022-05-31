#include "postgres_producers_repository.h"
#include <iostream>
#include "base_sections.h"
#include "database_exceptions.h"

PostgresProducersRepository::PostgresProducersRepository(
    const std::shared_ptr<BaseConfig>& conf,
    const std::string& connection_section) {
  read_config(conf, connection_section);
  connect();
  add_prepare_statements();
}

void PostgresProducersRepository::read_config(
    const std::shared_ptr<BaseConfig>& conf,
    const std::string& connection_section) {
  name_ = conf->get_string_field({connection_section, DbNameSection});
  user_ = conf->get_string_field({connection_section, DbUserSection});
  user_password_ =
      conf->get_string_field({connection_section, DbUserPasswordSection});
  host_ = conf->get_string_field({connection_section, DbHostSection});
  port_ = conf->get_uint_field({connection_section, DbPortSection});
}

void PostgresProducersRepository::connect() {
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

void PostgresProducersRepository::add_prepare_statements() {
  connection_->prepare(requests_names[CREATE],
                       "SELECT FN_ADD_PRODUCER($1, $2)");
  connection_->prepare(requests_names[READ_ALL],
                       "SELECT * FROM FN_GET_ALL_PRODUCERS()");
  connection_->prepare(requests_names[READ_BY_ID],
                       "SELECT * FROM FN_GET_PRODUCER_BY_ID($1)");
  connection_->prepare(requests_names[UPDATE],
                       "CALL PR_UPDATE_PRODUCER($1, $2, $3)");
  connection_->prepare(requests_names[DELETE], "CALL PR_DELETE_PRODUCER($1)");
}

size_t PostgresProducersRepository::create(
    const DetailsProducerData& producer) {
  try {
    pqxx::work w(*connection_);
    pqxx::result res = w.exec_prepared(requests_names[CREATE], producer.name(),
                                       producer.country());
    w.commit();

    return res[0][0].as<size_t>();
  } catch (...) {
    throw DatabaseExecutionException("can't execute prepared");
  }
}

DetailsProducer PostgresProducersRepository::read(size_t producer_id) {
  pqxx::result res;
  try {
    pqxx::work w(*connection_);
    res = w.exec_prepared(requests_names[READ_BY_ID], producer_id);
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

producers_t PostgresProducersRepository::read_all() {
  pqxx::result res;
  try {
    pqxx::work w(*connection_);
    res = w.exec_prepared(requests_names[READ_ALL]);
    w.commit();
  } catch (...) {
    throw DatabaseExecutionException("can't execute prepared");
  }

  producers_t producers;
  for (auto const& row : res) {
    producers.push_back(DetailsProducer(row["id"].as<size_t>(),
                                        row["name"].as<std::string>(),
                                        row["country"].as<std::string>()));
  }

  return producers;
}

void PostgresProducersRepository::update(const DetailsProducer& producer) {
  try {
    pqxx::work w(*connection_);
    w.exec_prepared(requests_names[UPDATE], producer.id(), producer.name(),
                    producer.country());
    w.commit();
  } catch (...) {
    throw DatabaseExecutionException("can't execute prepared");
  }
}

void PostgresProducersRepository::delete_(size_t producer_id) {
  try {
    pqxx::work w(*connection_);
    w.exec_prepared(requests_names[DELETE], producer_id);
    w.commit();
  } catch (...) {
    throw DatabaseExecutionException("can't execute prepared");
  }
}
