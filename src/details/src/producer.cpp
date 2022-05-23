#include "producer.h"
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include "server_exceptions.h"

DetailsProducer::DetailsProducer(size_t id,
                                 const std::string& name,
                                 const std::string& country)
    : id_(id), DetailsProducerData(name, country) {}

DetailsProducer::DetailsProducer(size_t id, const DetailsProducerData& data)
    : id_(id), DetailsProducerData(data) {}

std::string DetailsProducerData::name() const {
  return name_;
}

void DetailsProducerData::set_name(const std::string& name) {
  name_ = name;
}

std::string DetailsProducerData::country() const {
  return country_;
}

void DetailsProducerData::set_country(const std::string& country) {
  country_ = country;
}

bool DetailsProducerData::operator==(const DetailsProducerData& data) const {
  return (name_ == data.name_) && (country_ == data.country_);
}

size_t DetailsProducer::id() const {
  return id_;
}

void DetailsProducer::set_id(const size_t& id) {
  id_ = id;
}

bool DetailsProducer::operator==(const DetailsProducer& producer) const {
  return (id_ == producer.id_) && (name_ == producer.name_) &&
         (country_ == producer.country_);
}

DetailsProducerData::DetailsProducerData(const std::string& name,
                                         const std::string& country)
    : name_(name), country_(country) {}

DetailsProducerData::DetailsProducerData(const std::string& json_str) {
  Json::Value value;
  Json::Reader reader;

  bool parse_successfull = reader.parse(json_str, value);

  if (!parse_successfull) {
    throw JsonParserException("can't parse Details Producer object");
  }

  name_ = value["name"].asString();
  country_ = value["country"].asString();
}
