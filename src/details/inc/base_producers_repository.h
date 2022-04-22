#ifndef BASEPRODUCERSREPOSITORY_H
#define BASEPRODUCERSREPOSITORY_H

#include "producer.h"

class BaseProducersRepository {
 public:
  virtual size_t create(const DetailsProducerData& producer) = 0;
  virtual DetailsProducer read(size_t producer_id) = 0;
  virtual producers_t read_all() = 0;
  virtual void update(const DetailsProducer& producer) = 0;
  virtual void delete_(size_t producer_id) = 0;
};

#endif  // BASEPRODUCERSREPOSITORY_H
