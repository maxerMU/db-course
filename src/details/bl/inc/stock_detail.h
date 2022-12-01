#ifndef STOCKDETAIL_H
#define STOCKDETAIL_H

#include <string>
#include <vector>

class StockDetail
{
public:
    StockDetail(const std::string &part_number,
                const std::string &part_name,
                const std::string &producer_name,
                const std::string &producer_country,
                size_t amount);

    std::string get_part_number() const;
    void set_part_number(const std::string &value);

    std::string get_part_name() const;
    void set_part_name(const std::string &value);

    std::string get_producer_name() const;
    void set_producer_name(const std::string &value);

    std::string get_producer_country() const;
    void set_producer_country(const std::string &value);

    size_t get_amount() const;
    void set_amount(const size_t &value);

protected:
    std::string part_number;
    std::string part_name;
    std::string producer_name;
    std::string producer_country;
    size_t amount;
};

typedef std::vector<StockDetail> StockDetails;

#endif // STOCKDETAIL_H
