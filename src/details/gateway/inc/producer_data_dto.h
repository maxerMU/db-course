#ifndef PRODUCERDATADTO_H
#define PRODUCERDATADTO_H

#include "producer.h"

class ProducerDataDto : public DetailsProducerData
{
public:
    ProducerDataDto();
    ProducerDataDto(const std::string& json_str);
};

#endif // PRODUCERDATADTO_H
