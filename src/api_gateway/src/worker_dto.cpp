#include "worker_dto.h"

#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>

#include "server_exceptions.h"

WorkerDto::WorkerDto(const std::string &json_str) {
  Json::Value value;
  Json::Reader reader;

  bool parse_successfull = reader.parse(json_str, value);

  if (!parse_successfull) {
    throw JsonParserException("can't parse WorkerAuth object");
  }

  name = value["name"].asString();
  surname = value["surname"].asString();
}

std::string WorkerDto::get_name() const { return name; }

void WorkerDto::set_name(const std::string &value) { name = value; }

std::string WorkerDto::get_surname() const { return surname; }

void WorkerDto::set_surname(const std::string &value) { surname = value; }
