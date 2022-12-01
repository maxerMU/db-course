#ifndef STOCKCONTROLLER_H
#define STOCKCONTROLLER_H

#include "base_details_repository.h"
#include "base_producers_repository.h"
#include "base_stock_repository.h"
#include "stock_detail.h"
#include "stock_order.h"

class StockController {
 public:
  StockController(const std::shared_ptr<BaseDetailsRepository> &details_rep,
                  const std::shared_ptr<BaseProducersRepository> &producers_rep,
                  const std::shared_ptr<BaseStockRepository> &stock_rep);
  StockDetails get_details_in_stock();
  StockOrders get_orders(const std::string &time_start,
                         const std::string &time_end);

 private:
  std::shared_ptr<BaseDetailsRepository> details_rep_;
  std::shared_ptr<BaseProducersRepository> producers_rep_;
  std::shared_ptr<BaseStockRepository> stock_rep_;
};

#endif  // STOCKCONTROLLER_H
