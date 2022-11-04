#include "stock_log.h"

StockLog::StockLog(const size_t& fk_worker,
                   const std::string& fk_detail,
                   const int& change,
                   const std::string& time_change)
    : fk_worker_(fk_worker),
      fk_detail_(fk_detail),
      change_(change),
      time_change_(time_change) {}

size_t StockLog::fk_worker() const {
  return fk_worker_;
}

void StockLog::set_fk_worker(const size_t& fk_worker) {
  fk_worker_ = fk_worker;
}

std::string StockLog::fk_detail() const {
  return fk_detail_;
}

void StockLog::set_fk_detail(const std::string& fk_detail) {
  fk_detail_ = fk_detail;
}

int StockLog::change() const {
  return change_;
}

void StockLog::set_change(int change) {
  change_ = change;
}

std::string StockLog::time_change() const {
  return time_change_;
}

void StockLog::set_time_change(const std::string& time_change) {
  time_change_ = time_change;
}
