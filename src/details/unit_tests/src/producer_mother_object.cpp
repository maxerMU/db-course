#include "producer_mother_object.h"

ProducerMotherObject::ProducerMotherObject()
    : producer_(DetailsProducer(1, "test", "test")),
      producer_data_(DetailsProducerData("test", "test")) {
  producers_.push_back(DetailsProducer(1, "test", "test"));
  producers_.push_back(DetailsProducer(2, "test2", "test7"));
  producers_.push_back(DetailsProducer(3, "test4", "test5"));
  producers_.push_back(DetailsProducer(4, "test6", "test3"));
  producers_.push_back(DetailsProducer(5, "test8", "test1"));
}

DetailsProducer ProducerMotherObject::create_producer() {
  return producer_;
}

DetailsProducerData ProducerMotherObject::create_producer_data() {
  return producer_data_;
}

producers_t ProducerMotherObject::create_producers() {
  return producers_;
}
