#include "producer_data_dto.h"
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>
#include "server_exceptions.h"

ProducerDataDto::ProducerDataDto()
{
}

ProducerDataDto::ProducerDataDto(const std::string& json_str) {
  Json::Value value;
  Json::Reader reader;

  bool parse_successfull = reader.parse(json_str, value);

  if (!parse_successfull) {
    throw JsonParserException("can't parse Details Producer object");
  }

  name_ = value["name"].asString();
  country_ = value["country"].asString();
}
