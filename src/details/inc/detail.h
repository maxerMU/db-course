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
         const std::shared_ptr<DetailsProducer> producer);

  std::string name_rus() const;
  void set_name_rus(const std::string& name_rus);

  std::string name_eng() const;
  void set_name_eng(const std::string& name_eng);

  std::string part_number() const;
  void set_part_number(const std::string& part_number);

  std::shared_ptr<DetailsProducer> producer() const;
  void set_producer(const std::shared_ptr<DetailsProducer>& producer);

 private:
  std::string name_rus_;
  std::string name_eng_;
  std::string part_number_;
  std::shared_ptr<DetailsProducer> producer_;
};

#endif  // DETAIL_H
