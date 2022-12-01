#include "detail_to_stock_dto.h"
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>
#include "server_exceptions.h"

DetailToStockDto::DetailToStockDto(const std::string& part_number,
                                   size_t quantity)
    : part_number(part_number), quantity(quantity) {}

DetailToStockDto::DetailToStockDto(const std::string& json_str) {
  Json::Value value;
  Json::Reader reader;

  bool parse_successfull = reader.parse(json_str, value);

  if (!parse_successfull) {
    throw JsonParserException("can't parse request data");
  }

  part_number = value["part_number"].asString();
  quantity = value["quantity"].asUInt64();
}

size_t DetailToStockDto::get_quantity() const {
  return quantity;
}

void DetailToStockDto::set_quantity(const size_t& value) {
  quantity = value;
}

std::string DetailToStockDto::get_part_number() const {
  return part_number;
}

void DetailToStockDto::set_part_number(const std::string& value) {
  part_number = value;
}
