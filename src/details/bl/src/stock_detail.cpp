#include "stock_detail.h"

StockDetail::StockDetail(const std::string &part_number, const std::string &part_name, const std::string &producer_name, const std::string &producer_country, size_t amount)
    :part_number(part_number), part_name(part_name), producer_name(producer_name), producer_country(producer_country), amount(amount)
{

}

std::string StockDetail::get_part_number() const
{
    return part_number;
}

void StockDetail::set_part_number(const std::string &value)
{
    part_number = value;
}

std::string StockDetail::get_part_name() const
{
    return part_name;
}

void StockDetail::set_part_name(const std::string &value)
{
    part_name = value;
}

std::string StockDetail::get_producer_name() const
{
    return producer_name;
}

void StockDetail::set_producer_name(const std::string &value)
{
    producer_name = value;
}

std::string StockDetail::get_producer_country() const
{
    return producer_country;
}

void StockDetail::set_producer_country(const std::string &value)
{
    producer_country = value;
}

size_t StockDetail::get_amount() const
{
    return amount;
}

void StockDetail::set_amount(const size_t &value)
{
    amount = value;
}
