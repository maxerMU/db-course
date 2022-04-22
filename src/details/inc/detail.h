#ifndef DETAIL_H
#define DETAIL_H

#include <memory>
#include "producer.h"

class Detail {
 public:
  Detail() = default;
  Detail(const std::string& name_rus,
         const std::string& name_eng,
         const std::string& part_number,
         size_t producer_id);
  Detail(const std::string& json_str);

  std::string name_rus() const;
  void set_name_rus(const std::string& name_rus);

  std::string name_eng() const;
  void set_name_eng(const std::string& name_eng);

  std::string part_number() const;
  void set_part_number(const std::string& part_number);

  size_t producer_id() const;
  void set_producer_id(const size_t& producer_id);

 private:
  std::string name_rus_;
  std::string name_eng_;
  std::string part_number_;
  size_t producer_id_;
};

typedef std::vector<Detail> details_t;

#endif  // DETAIL_H
