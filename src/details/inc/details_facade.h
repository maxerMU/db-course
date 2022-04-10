#ifndef DETAILSFACADE_H
#define DETAILSFACADE_H

#include <memory>
#include <vector>
#include "detail.h"

typedef std::vector<Detail> details_t;
typedef std::vector<DetailsProducer> producers_t;

class DetailsFacade {
 private:
  DetailsFacade();
  DetailsFacade(const DetailsFacade&) = delete;

 public:
  static DetailsFacade& instanse() {
    static DetailsFacade facade;
    return facade;
  }

  details_t get_details_for_all_time();
  details_t get_details_in_stock();
  details_t get_detail_swaps(const std::string& part_number);

  void add_detail(const Detail& detail);
  void add_detail_swap(const Detail& detail, const Detail& swap);
  void add_details(const details_t& details);

  void add_producer(const DetailsProducer& producer);
  producers_t get_producers();
};

#endif  // DETAILSFACADE_H
