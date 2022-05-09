#ifndef DETAILSFACADE_H
#define DETAILSFACADE_H

#include <memory>
#include <vector>
#include "base_config.h"
#include "detail.h"
#include "postgres_details_repository.h"
#include "postgres_producers_repository.h"
#include "postgres_stock_repository.h"
#include "postgres_swaps_repository.h"
#include "swaps_controller.h"

const std::string DbProducersSection = "DB_PRODUCERS";
const std::string DbDetailsSection = "DB_DETAILS";
const std::string DbSwapsSection = "DB_SWAPS";
const std::string DbStockSection = "DB_STOCK";

class DetailsFacade {
 private:
  DetailsFacade();
  DetailsFacade(const DetailsFacade&) = delete;

 public:
  static DetailsFacade& instanse() {
    static DetailsFacade facade;
    return facade;
  }

  void init(const std::shared_ptr<BaseConfig>& conf);

  /*details branch */
  details_t get_details();
  Detail get_detail(const std::string& part_name);
  void add_detail(const Detail& detail);
  void update_detail(const Detail& detail);
  void delete_detail(const std::string& part_name);

  /* swaps branch */
  void add_detail_swap(const std::string& src, const std::string& dst);
  details_t get_detail_swaps(const std::string& src);
  void delete_detail_swap(const std::string& src, const std::string& dst);

  /* stock branch */
  void add_detail_to_stock(const std::string& part_name,
                           size_t worker_id,
                           size_t quantity);

  void remove_detail_from_stock(const std::string& part_name,
                                size_t worker_id,
                                size_t quantity);
  details_quantities_t get_details_in_stock();
  details_names_t get_prev_details_in_stock();
  detail_quantity_t get_detail_in_stock(const std::string& part_name);

  // void add_details(const details_t& details);

  /* producers branch */
  size_t add_producer(const DetailsProducerData& producer);
  producers_t get_producers();
  DetailsProducer get_producer(size_t id);
  void delete_producer(size_t id);
  void update_producer(const DetailsProducer& producer);

 private:
  std::shared_ptr<BaseConfig> config_;
  std::shared_ptr<BaseProducersRepository> producers_db_;
  std::shared_ptr<BaseDetailsRepository> details_db_;
  std::shared_ptr<BaseSwapsRepository> swaps_db_;
  std::shared_ptr<BaseStockRepository> stock_db_;
  std::shared_ptr<SwapsController> swaps_controller_;
};

#endif  // DETAILSFACADE_H
