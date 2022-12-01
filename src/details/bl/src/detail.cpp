#include "detail.h"
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include "server_exceptions.h"

Detail::Detail(const std::string& name_rus,
               const std::string& name_eng,
               const std::string& part_number,
               size_t producer_id)
    : name_rus_(name_rus),
      name_eng_(name_eng),
      part_number_(part_number),
      producer_id_(producer_id) {}

std::string Detail::name_rus() const {
  return name_rus_;
}

void Detail::set_name_rus(const std::string& name_rus) {
  name_rus_ = name_rus;
}

std::string Detail::name_eng() const {
  return name_eng_;
}

void Detail::set_name_eng(const std::string& name_eng) {
  name_eng_ = name_eng;
}

std::string Detail::part_number() const {
  return part_number_;
}

void Detail::set_part_number(const std::string& part_number) {
  part_number_ = part_number;
}

size_t Detail::producer_id() const {
  return producer_id_;
}

void Detail::set_producer_id(const size_t& producer_id) {
  producer_id_ = producer_id;
}

bool Detail::operator==(const Detail& detail) const {
  return (producer_id_ == detail.producer_id_) &&
         (part_number_ == detail.part_number_) &&
         (name_rus_ == detail.name_rus_) && (name_eng_ == detail.name_eng_);
}
