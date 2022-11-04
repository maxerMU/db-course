#ifndef DETAILDTO_H
#define DETAILDTO_H

#include "detail.h"

class DetailDto : public Detail
{
public:
    DetailDto();
    DetailDto(const std::string& json_str);
    DetailDto(const std::string& part_number, const std::string& json_data);

};

#endif // DETAILDTO_H
