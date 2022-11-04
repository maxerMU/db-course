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

  std::string name_rus() const;
  void set_name_rus(const std::string& name_rus);

  std::string name_eng() const;
  void set_name_eng(const std::string& name_eng);

  std::string part_number() const;
  void set_part_number(const std::string& part_number);

  size_t producer_id() const;
  void set_producer_id(const size_t& producer_id);

  bool operator==(const Detail& detail) const;

 protected:
  std::string name_rus_;
  std::string name_eng_;
  std::string part_number_;
  size_t producer_id_;
};

typedef std::vector<Detail> details_t;
typedef std::pair<std::string, size_t> detail_quantity_t;
typedef std::vector<std::string> details_names_t;
typedef std::vector<detail_quantity_t> details_quantities_t;

#endif  // DETAIL_H
