#ifndef STOCKORDERS_H
#define STOCKORDERS_H

#include <string>
#include <vector>

class StockOrder {
 public:
  StockOrder(const std::string &part_number, const std::string &worker,
             size_t change, const std::string &date);

  std::string get_part_number() const;
  void set_part_number(const std::string &value);

  std::string get_worker() const;
  void set_worker(const std::string &value);

  size_t get_change() const;
  void set_change(const size_t &value);

  std::string get_date() const;
  void set_date(const std::string &value);

 protected:
  std::string part_number;
  std::string worker;
  size_t change;
  std::string date;
};

typedef std::vector<StockOrder> StockOrders;

#endif  // STOCKORDERS_H
