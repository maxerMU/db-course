#ifndef BASE_STOCK_REPOSITORY_H
#define BASE_STOCK_REPOSITORY_H

#include "detail.h"

class BaseStockRepository {
 public:
  virtual void create(const std::string &part_name, size_t worker_id, size_t quantity) = 0;
  virtual detail_quantity_t read(const std::string &part_name) = 0;
  virtual details_quantities_t read_current() = 0;
  virtual details_names_t read_prev() = 0;
  virtual void delete_(const std::string &part_name, size_t worker_id, size_t quantity) = 0;
};

#endif // BASE_STOCK_REPOSITORY_H
