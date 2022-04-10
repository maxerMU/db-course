#include "detail.h"

Detail::Detail(const std::string &name_rus, const std::string &name_eng,
               const std::string &part_number,
               const std::shared_ptr<DetailsProducer> producer)
    : name_rus_(name_rus), name_eng_(name_eng), part_number_(part_number),
      producer_(producer) {}

std::string Detail::name_rus() const { return name_rus_; }

void Detail::set_name_rus(const std::string &name_rus) { name_rus_ = name_rus; }

std::string Detail::name_eng() const { return name_eng_; }

void Detail::set_name_eng(const std::string &name_eng) { name_eng_ = name_eng; }

std::string Detail::part_number() const { return part_number_; }

void Detail::set_part_number(const std::string &part_number) {
  part_number_ = part_number;
}

std::shared_ptr<DetailsProducer> Detail::producer() const { return producer_; }

void Detail::set_producer(const std::shared_ptr<DetailsProducer> &producer) {
  producer_ = producer;
}
