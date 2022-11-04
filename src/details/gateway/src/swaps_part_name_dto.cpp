#include "swaps_part_name_dto.h"
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>
#include "server_exceptions.h"

SwapsPartNameDto::SwapsPartNameDto(const std::string& json_str) {
  Json::Value val;
  Json::Reader reader;

  bool parse_successfull = reader.parse(json_str, val);

  if (!parse_successfull) {
    throw JsonParserException("can't parse add detail swaps request");
  }

  part_dst = val["swap_part_numbers"].asString();
}

std::string SwapsPartNameDto::get_part_dst() const {
  return part_dst;
}

void SwapsPartNameDto::set_part_dst(const std::string& value) {
  part_dst = value;
}
