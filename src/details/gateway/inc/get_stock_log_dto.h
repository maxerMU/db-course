#ifndef GETSTOCKLOGDTO_H
#define GETSTOCKLOGDTO_H

#include <string>

class GetStockLogDto
{
public:
    GetStockLogDto(const std::string &time_start, const std::string &time_end);
    GetStockLogDto(const std::string &json_str);

    std::string get_time_start() const;
    void set_time_start(const std::string &value);

    std::string get_time_end() const;
    void set_time_end(const std::string &value);

private:
    std::string time_start;
    std::string time_end;
};

#endif // GETSTOCKLOGDTO_H
