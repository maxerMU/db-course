#ifndef POSTGRESPRODUCERSREPOSITORY_H
#define POSTGRESPRODUCERSREPOSITORY_H

#include <map>
#include <pqxx/pqxx>
#include "base_config.h"
#include "base_producers_repository.h"

class PostgresProducersRepository : public BaseProducersRepository {
 public:
  PostgresProducersRepository(const std::shared_ptr<BaseConfig>& conf,
                              const std::string& connection_section);

  virtual size_t create(const DetailsProducerData& producer) override;
  virtual DetailsProducer read(size_t producer_id) override;
  virtual producers_t read_all() override;
  virtual void update(const DetailsProducer& producer) override;
  virtual void delete_(size_t producer_id) override;

 private:
  void read_config(const std::shared_ptr<BaseConfig>& conf,
                   const std::string& connection_section);

  void connect();
  void add_prepare_statements();

  std::shared_ptr<pqxx::connection> connection_;

  std::string name_;
  std::string user_;
  std::string user_password_;
  std::string host_;
  size_t port_;

  enum PreparedRequests { CREATE, READ_ALL, READ_BY_ID, UPDATE, DELETE };

  std::map<PreparedRequests, std::string> requests_names = {
      {CREATE, "create_producer"},
      {READ_ALL, "read_all_producers"},
      {READ_BY_ID, "read_producer_by_id"},
      {UPDATE, "update_producer"},
      {DELETE, "delete_producer"}};
};

#endif  // POSTGRESPRODUCERSREPOSITORY_H
