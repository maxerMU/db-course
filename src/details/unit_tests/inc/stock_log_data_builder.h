#ifndef STOCKLOGDATABUILDER_H
#define STOCKLOGDATABUILDER_H

#include "stock_log.h"

class StockLogDataBuilder {
 public:
  StockLogDataBuilder() = default;

  StockLogDataBuilder* with_fk_worker(size_t fk_worker);
  StockLogDataBuilder* with_fk_detail(const std::string& fk_detail);
  StockLogDataBuilder* with_change(int change);
  StockLogDataBuilder* with_time_change(const std::string& time_change);
  StockLog build();

 private:
  StockLog stock_log_;
};

#endif  // STOCKLOGDATABUILDER_H
