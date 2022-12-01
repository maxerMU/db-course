#ifndef STOCKLOG_H
#define STOCKLOG_H

#include <vector>
#include <string>

class StockLog {
 public:
  StockLog() = default;
  StockLog(const size_t& fk_worker,
           const std::string& fk_detail,
           const int& change,
           const std::string& time_change);

  size_t fk_worker() const;
  void set_fk_worker(const size_t& fk_worker);

  std::string fk_detail() const;
  void set_fk_detail(const std::string& fk_detail);

  int change() const;
  void set_change(int change);

  std::string time_change() const;
  void set_time_change(const std::string& time_change);

 private:
  size_t fk_worker_;
  std::string fk_detail_;
  int change_;
  std::string time_change_;
};

typedef std::vector<StockLog> stock_logs_t;

#endif // STOCKLOG_H
