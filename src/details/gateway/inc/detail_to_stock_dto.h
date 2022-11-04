#ifndef DETAILTOSTOCKDTO_H
#define DETAILTOSTOCKDTO_H

#include <string>

class DetailToStockDto
{
public:
    DetailToStockDto(const std::string &part_number, size_t quantity);
    DetailToStockDto(const std::string &json_str);

    std::string get_part_number() const;
    void set_part_number(const std::string &value);

    size_t get_quantity() const;
    void set_quantity(const size_t &value);

private:
    std::string part_number;
    size_t quantity;
};

#endif // DETAILTOSTOCKDTO_H
