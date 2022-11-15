#ifndef PRODUCERMOTHEROBJECT_H
#define PRODUCERMOTHEROBJECT_H

#include "producer.h"

class ProducerMotherObject
{
public:
    ProducerMotherObject();

    DetailsProducer create_producer();
    DetailsProducerData create_producer_data();
    producers_t create_producers();

private:
    DetailsProducerData producer_data_;
    DetailsProducer producer_;
    producers_t producers_;
};

#endif // PRODUCERMOTHEROBJECT_H
