#include "details_facade.h"

DetailsFacade::DetailsFacade() {}

void DetailsFacade::init(const std::shared_ptr<BaseConfig>& conf) {
  config_ = conf;

  producers_db_ = std::shared_ptr<BaseProducersRepository>(
      new PostgresProducersRepository(conf, DbProducersSection));

  details_db_ = std::shared_ptr<BaseDetailsRepository>(
      new PostgresDetailsRepository(conf, DbDetailsSection));
}

details_t DetailsFacade::get_details() {
  return details_db_->read_all();
}

Detail DetailsFacade::get_detail(const std::string& part_name) {
  return details_db_->read(part_name);
}

void DetailsFacade::add_detail(const Detail& detail) {
  details_db_->create(detail);
}

size_t DetailsFacade::add_producer(const DetailsProducerData& producer) {
  return producers_db_->create(producer);
}

producers_t DetailsFacade::get_producers() {
  return producers_db_->read_all();
}

DetailsProducer DetailsFacade::get_producer(size_t id) {
  return producers_db_->read(id);
}

void DetailsFacade::delete_producer(size_t id) {
  producers_db_->delete_(id);
}

void DetailsFacade::update_producer(const DetailsProducer& producer) {
  producers_db_->update(producer);
}
