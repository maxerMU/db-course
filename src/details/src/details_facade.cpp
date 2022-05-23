#include "details_facade.h"
#include <iostream>

DetailsFacade::DetailsFacade() {}

void DetailsFacade::init(
    const std::shared_ptr<BaseConfig>& conf,
    const std::shared_ptr<BaseProducersRepository>& producers_rep,
    const std::shared_ptr<BaseDetailsRepository>& details_rep,
    const std::shared_ptr<BaseSwapsRepository>& swaps_rep,
    const std::shared_ptr<BaseStockRepository>& stock_rep) {
  config_ = conf;
  producers_rep_ = producers_rep;
  details_rep_ = details_rep;
  swaps_rep_ = swaps_rep;
  stock_rep_ = stock_rep;

  swaps_controller_ = std::shared_ptr<SwapsController>(
      new SwapsController(swaps_rep_, details_rep_));
}

details_t DetailsFacade::get_details() {
  return details_rep_->read_all();
}

Detail DetailsFacade::get_detail(const std::string& part_name) {
  return details_rep_->read(part_name);
}

void DetailsFacade::add_detail(const Detail& detail) {
  details_rep_->create(detail);
}

void DetailsFacade::update_detail(const Detail& detail) {
  details_rep_->update(detail);
}

void DetailsFacade::delete_detail(const std::string& part_name) {
  details_rep_->delete_(part_name);
}

void DetailsFacade::add_detail_swap(const std::string& src,
                                    const std::string& dst) {
  swaps_controller_->add_swap(src, dst);
}

details_t DetailsFacade::get_detail_swaps(const std::string& src) {
  return swaps_controller_->get_swaps(src);
}

void DetailsFacade::delete_detail_swap(const std::string& src,
                                       const std::string& dst) {
  swaps_controller_->remove_swap(src, dst);
}

void DetailsFacade::add_detail_to_stock(const std::string& part_name,
                                        size_t worker_id,
                                        size_t quantity) {
  stock_rep_->create(part_name, worker_id, quantity);
}

void DetailsFacade::remove_detail_from_stock(const std::string& part_name,
                                             size_t worker_id,
                                             size_t quantity) {
  stock_rep_->delete_(part_name, worker_id, quantity);
}

details_quantities_t DetailsFacade::get_details_in_stock() {
  return stock_rep_->read_current();
}

details_names_t DetailsFacade::get_prev_details_in_stock() {
  return stock_rep_->read_prev();
}

detail_quantity_t DetailsFacade::get_detail_in_stock(
    const std::string& part_name) {
  return stock_rep_->read(part_name);
}

size_t DetailsFacade::add_producer(const DetailsProducerData& producer) {
  return producers_rep_->create(producer);
}

producers_t DetailsFacade::get_producers() {
  return producers_rep_->read_all();
}

DetailsProducer DetailsFacade::get_producer(size_t id) {
  return producers_rep_->read(id);
}

void DetailsFacade::delete_producer(size_t id) {
  producers_rep_->delete_(id);
}

void DetailsFacade::update_producer(const DetailsProducer& producer) {
  producers_rep_->update(producer);
}
