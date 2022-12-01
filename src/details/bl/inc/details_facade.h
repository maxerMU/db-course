#ifndef DETAILSFACADE_H
#define DETAILSFACADE_H

#include <memory>
#include <vector>

#include "base_config.h"
#include "base_details_repository.h"
#include "base_producers_repository.h"
#include "base_stock_repository.h"
#include "base_swaps_repository.h"
#include "detail.h"
#include "stock_controller.h"
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

  void init(const std::shared_ptr<BaseConfig>& conf,
            const std::shared_ptr<BaseProducersRepository>& producers_rep,
            const std::shared_ptr<BaseDetailsRepository>& details_rep,
            const std::shared_ptr<BaseSwapsRepository>& swaps_rep,
            const std::shared_ptr<BaseStockRepository>& stock_rep);

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
  void add_detail_to_stock(const std::string& part_name, size_t worker_id,
                           size_t quantity);

  void remove_detail_from_stock(const std::string& part_name, size_t worker_id,
                                size_t quantity);
  StockDetails get_details_in_stock();
  details_names_t get_prev_details_in_stock();
  detail_quantity_t get_detail_in_stock(const std::string& part_name);
  stock_logs_t get_logs(const std::string& time_start,
                        const std::string& time_end);

  /* producers branch */
  size_t add_producer(const DetailsProducerData& producer);
  producers_t get_producers();
  DetailsProducer get_producer(size_t id);
  void delete_producer(size_t id);
  void update_producer(const DetailsProducer& producer);

 private:
  std::shared_ptr<BaseConfig> config_;
  std::shared_ptr<BaseProducersRepository> producers_rep_;
  std::shared_ptr<BaseDetailsRepository> details_rep_;
  std::shared_ptr<BaseSwapsRepository> swaps_rep_;
  std::shared_ptr<BaseStockRepository> stock_rep_;
  std::shared_ptr<SwapsController> swaps_controller_;
  std::shared_ptr<StockController> stock_controller_;
};

#endif  // DETAILSFACADE_H
