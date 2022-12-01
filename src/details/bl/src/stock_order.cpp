#include "stock_order.h"

StockOrder::StockOrder(const std::string &part_number,
                       const std::string &worker, size_t change,
                       const std::string &date)
    : part_number(part_number), worker(worker), change(change), date(date) {}

std::string StockOrder::get_part_number() const { return part_number; }

void StockOrder::set_part_number(const std::string &value) {
  part_number = value;
}

std::string StockOrder::get_worker() const { return worker; }

void StockOrder::set_worker(const std::string &value) { worker = value; }

size_t StockOrder::get_change() const { return change; }

void StockOrder::set_change(const size_t &value) { change = value; }

std::string StockOrder::get_date() const { return date; }

void StockOrder::set_date(const std::string &value) { date = value; }
