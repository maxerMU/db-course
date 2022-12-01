#include "stock_log_data_builder.h"

StockLogDataBuilder* StockLogDataBuilder::with_fk_worker(size_t fk_worker) {
  stock_log_.set_fk_worker(fk_worker);
  return this;
}

StockLogDataBuilder* StockLogDataBuilder::with_fk_detail(
    const std::string& fk_detail) {
  stock_log_.set_fk_detail(fk_detail);
  return this;
}

StockLogDataBuilder* StockLogDataBuilder::with_change(int change) {
  stock_log_.set_change(change);
  return this;
}

StockLogDataBuilder* StockLogDataBuilder::with_time_change(
    const std::string& time_change) {
  stock_log_.set_time_change(time_change);
  return this;
}

StockLog StockLogDataBuilder::build() {
  return stock_log_;
}
