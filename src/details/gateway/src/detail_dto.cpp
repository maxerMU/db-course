#include "detail_dto.h"
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>
#include "server_exceptions.h"

DetailDto::DetailDto() {}

DetailDto::DetailDto(const std::string& json_str) {
  Json::Value value;
  Json::Reader reader;

  bool parse_successfull = reader.parse(json_str, value);

  if (!parse_successfull) {
    throw JsonParserException("can't parse Detail object");
  }

  name_rus_ = value["name_rus"].asString();
  name_eng_ = value["name_eng"].asString();
  part_number_ = value["part_number"].asString();
  producer_id_ = value["producer_id"].asUInt64();
}

DetailDto::DetailDto(const std::string& part_number,
                     const std::string& json_data) {
  Json::Value value;
  Json::Reader reader;

  bool parse_successfull = reader.parse(json_data, value);

  if (!parse_successfull) {
    throw JsonParserException("can't parse Detail object");
  }

  name_rus_ = value["name_rus"].asString();
  name_eng_ = value["name_eng"].asString();
  producer_id_ = value["producer_id"].asUInt64();
  part_number_ = part_number;
}
