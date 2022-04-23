#ifndef DETAILSFACADE_H
#define DETAILSFACADE_H

#include <memory>
#include <vector>
#include "base_config.h"
#include "detail.h"
#include "postgres_details_repository.h"
#include "postgres_producers_repository.h"

const std::string DbProducersSection = "DB_PRODUCERS";
const std::string DbDetailsSection = "DB_DETAILS";

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

  details_t get_details_for_all_time();
  details_t get_details_in_stock();
  details_t get_detail_swaps(const std::string& part_number);

  void add_detail_swaps(const std::string& part_number,
                        const std::vector<std::string>& swaps);
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
};

#endif  // DETAILSFACADE_H
