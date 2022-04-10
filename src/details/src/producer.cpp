#include "producer.h"

DetailsProducer::DetailsProducer(const std::string &name,
                                 const std::string &country)
    : name_(name), country_(country) {}

std::string DetailsProducer::name() const { return name_; }

void DetailsProducer::set_name(const std::string &name) { name_ = name; }

std::string DetailsProducer::country() const { return country_; }

void DetailsProducer::set_country(const std::string &country) {
  country_ = country;
}
