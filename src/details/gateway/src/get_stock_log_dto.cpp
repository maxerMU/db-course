#include "get_stock_log_dto.h"
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>
#include "server_exceptions.h"

GetStockLogDto::GetStockLogDto(const std::string& time_start,
                               const std::string& time_end)
    : time_start(time_start), time_end(time_end) {}

GetStockLogDto::GetStockLogDto(const std::string& json_str) {
  Json::Value value;
  Json::Reader reader;

  bool parse_successfull = reader.parse(json_str, value);

  if (!parse_successfull) {
    throw JsonParserException("can't parse request data");
  }

  time_start = value["time_start"].asString();
  time_end = value["time_end"].asString();
}

std::string GetStockLogDto::get_time_end() const {
  return time_end;
}

void GetStockLogDto::set_time_end(const std::string& value) {
  time_end = value;
}

std::string GetStockLogDto::get_time_start() const {
  return time_start;
}

void GetStockLogDto::set_time_start(const std::string& value) {
  time_start = value;
}
