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

Detail::Detail(const std::string& json_str) {
  Json::Value value;
  Json::Reader reader;

  bool parse_successfull = reader.parse(json_str, value);

  if (!parse_successfull) {
    throw JsonParserException("can't parse Detail object");
  }

  name_rus_ = value["name_rus"].asString();
  name_eng_ = value["name_eng"].asString();
  part_number_ = value["part_number"].asString();
  producer_id_ = value["producer_id"].asUInt64();
}

Detail::Detail(const std::string& part_number, const std::string& json_data) {
  Json::Value value;
  Json::Reader reader;

  bool parse_successfull = reader.parse(json_data, value);

  if (!parse_successfull) {
    throw JsonParserException("can't parse Detail object");
  }

  name_rus_ = value["name_rus"].asString();
  name_eng_ = value["name_eng"].asString();
  producer_id_ = value["producer_id"].asUInt64();
  part_number_ = part_number;
}

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
