#include "stock_controller.h"

StockController::StockController(
    const std::shared_ptr<BaseDetailsRepository> &details_rep,
    const std::shared_ptr<BaseProducersRepository> &producers_rep,
    const std::shared_ptr<BaseStockRepository> &stock_rep)
    : details_rep_(details_rep),
      producers_rep_(producers_rep),
      stock_rep_(stock_rep) {}

StockDetails StockController::get_details_in_stock() {
  details_quantities_t details_quantities = stock_rep_->read_current();

  StockDetails stock_details;
  for (auto detail_quantity : details_quantities) {
    Detail detail = details_rep_->read(detail_quantity.first);
    DetailsProducer producer = producers_rep_->read(detail.producer_id());

    stock_details.push_back(
        StockDetail(detail_quantity.first, detail.name_eng(), producer.name(),
                    producer.country(), detail_quantity.second));
  }

  return stock_details;
}

StockOrders StockController::get_orders(const std::string &time_start,
                                        const std::string &time_end) {
  stock_logs_t logs = stock_rep_->read_log(time_start, time_end);

  StockOrders orders;
  for (auto log : logs) {
  }
}
