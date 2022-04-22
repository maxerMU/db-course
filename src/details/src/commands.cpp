#include "commands.h"
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>
#include <iostream>
#include "server_exceptions.h"

size_t get_producer_id_from_regex(const std::string& target,
                                  const std::regex& regexpr,
                                  size_t producer_id_group_index) {
  std::smatch match;
  std::string producer_id_str;
  if (std::regex_search(target, match, regexpr)) {
    producer_id_str = match.str(producer_id_group_index);
  } else {
    throw RegExpParserException("couldn't parse regexpr for producer id");
  }

  size_t producer_id;
  try {
    producer_id = std::stoll(producer_id_str);
  } catch (std::exception) {
    throw RegExpParserException("couldn't convert " + producer_id_str +
                                " to size_t");
  }

  return producer_id;
}

std::string get_part_number_from_regex(const std::string& target,
                                       const std::regex& regexpr,
                                       size_t part_number_group_index) {
  std::smatch match;

  std::string part_number;
  if (std::regex_search(target, match, regexpr)) {
    part_number = match.str(part_number_group_index);
  } else {
    throw RegExpParserException(
        "couldn't parse regexpr for DetailSwapsCommand");
  }

  return part_number;
}

void DetailsForAllTimeCommand::handle_request(
    const std::shared_ptr<Request>& req) {
  // details = DetailsFacade::instanse().get_details_for_all_time();
}

void DetailsForAllTimeCommand::get_response(
    const std::shared_ptr<Response>& resp) {
  Json::Value arr = Json::arrayValue;
  arr.append("1");
  arr.append("2");

  Json::Value root;
  root["details"] = arr;

  Json::FastWriter writer;
  resp->set_body(writer.write(root));
  resp->set_status(RESP_OK);
}

void DetailsInStockCommand::handle_request(
    const std::shared_ptr<Request>& req) {
  // details = DetailsFacade::instanse().get_details_in_stock();
}

void DetailsInStockCommand::get_response(
    const std::shared_ptr<Response>& resp) {
  Json::Value arr = Json::arrayValue;
  arr.append("3");
  arr.append("4");

  Json::Value root;
  root["details"] = arr;

  Json::FastWriter writer;
  resp->set_body(writer.write(root));
  resp->set_status(RESP_OK);
}

void DetailSwapsCommand::handle_request(const std::shared_ptr<Request>& req) {
  // details = DetailsFacade::instanse().get_detail_swaps(part_number_);
}

void DetailSwapsCommand::get_response(const std::shared_ptr<Response>& resp) {
  Json::Value arr = Json::arrayValue;
  arr.append("5");
  arr.append("6");

  Json::Value root;
  root["details"] = arr;

  Json::FastWriter writer;
  resp->set_body(writer.write(root));
  resp->set_status(RESP_OK);
}

void AddDetailCommand::handle_request(const std::shared_ptr<Request>& req) {
  auto detail = Detail(req->get_body());

  // DetailsFacade::instanse().add_detail(detail);
}

void AddDetailCommand::get_response(const std::shared_ptr<Response>& resp) {
  resp->set_status(RESP_OK);
}

void AddDetailSwapsCommand::handle_request(
    const std::shared_ptr<Request>& req) {
  std::smatch match;

  auto target = req->get_target();
  if (std::regex_search(target, match, regexpr_)) {
    part_number_ = match.str(part_number_group_index_);
    std::cout << part_number_ << std::endl;
  } else {
    throw RegExpParserException(
        "couldn't parse regexpr for DetailSwapsCommand");
  }

  Json::Value val;
  Json::Reader reader;

  bool parse_successfull = reader.parse(req->get_body(), val);

  if (!parse_successfull) {
    throw JsonParserException("can't parse add detail swaps request");
  }

  // part_number_ = val["part_number"].asString();

  const auto swaps = val["swaps_part_numbers"];
  for (int i = 0; i < swaps.size(); i++) {
    std::cout << swaps[i].asString() << std::endl;
    swaps_part_numbers_.push_back(swaps[i].asString());
  }

  // DetailsFacade::instanse().add_detail_swaps(part_number_,
  // swaps_part_numbers_);
}

void AddDetailSwapsCommand::get_response(
    const std::shared_ptr<Response>& resp) {
  resp->set_status(RESP_OK);
}

void GetProducersCommand::handle_request(const std::shared_ptr<Request>& req) {
  producers_ = DetailsFacade::instanse().get_producers();
}

void GetProducersCommand::get_response(const std::shared_ptr<Response>& resp) {
  Json::Value arr = Json::arrayValue;

  for (auto producer : producers_) {
    Json::Value root;
    root["id"] = std::to_string(producer.id());
    root["name"] = producer.name();
    root["country"] = producer.country();
    arr.append(root);
  }

  Json::Value root;
  root["producers"] = arr;

  Json::FastWriter writer;
  resp->set_body(writer.write(root));
  resp->set_status(RESP_OK);
}

void AddProducerCommand::handle_request(const std::shared_ptr<Request>& req) {
  auto producer = DetailsProducerData(req->get_body());

  id_ = DetailsFacade::instanse().add_producer(producer);
}

void AddProducerCommand::get_response(const std::shared_ptr<Response>& resp) {
  unsigned long long int tmp = id_;
  Json::Value root;
  root["id"] = tmp;

  Json::FastWriter writer;
  resp->set_body(writer.write(root));
  resp->set_status(RESP_OK);
}

void GetProducerByIdCommand::handle_request(
    const std::shared_ptr<Request>& req) {
  auto producer_id = get_producer_id_from_regex(req->get_target(), regexpr_,
                                                producer_id_group_index_);

  producer_ = DetailsFacade::instanse().get_producer(producer_id);
}

void GetProducerByIdCommand::get_response(
    const std::shared_ptr<Response>& resp) {
  Json::Value root;
  root["id"] = std::to_string(producer_.id());
  root["name"] = producer_.name();
  root["country"] = producer_.country();

  Json::FastWriter writer;
  resp->set_body(writer.write(root));
  resp->set_status(RESP_OK);
}

void DeleteProducerCommand::handle_request(
    const std::shared_ptr<Request>& req) {
  auto producer_id = get_producer_id_from_regex(req->get_target(), regexpr_,
                                                producer_id_group_index_);

  DetailsFacade::instanse().delete_producer(producer_id);
}

void DeleteProducerCommand::get_response(
    const std::shared_ptr<Response>& resp) {
  resp->set_status(RESP_OK);
}

void UpdateProducerCommand::handle_request(
    const std::shared_ptr<Request>& req) {
  auto producer_id = get_producer_id_from_regex(req->get_target(), regexpr_,
                                                producer_id_group_index_);

  DetailsProducerData producer_data(req->get_body());

  DetailsFacade::instanse().update_producer(
      DetailsProducer(producer_id, producer_data));
}

void UpdateProducerCommand::get_response(
    const std::shared_ptr<Response>& resp) {
  resp->set_status(RESP_OK);
}

void GetDetailsCommand::handle_request(const std::shared_ptr<Request>& req) {
  details_ = DetailsFacade::instanse().get_details();
}

void GetDetailsCommand::get_response(const std::shared_ptr<Response>& resp) {
  Json::Value arr = Json::arrayValue;

  for (auto detail : details_) {
    Json::Value root;
    root["part_number"] = detail.part_number();
    root["name_rus"] = detail.name_rus();
    root["name_eng"] = detail.name_eng();
    root["producer_id"] = std::to_string(detail.producer_id());
    arr.append(root);
  }

  Json::Value root;
  root["details"] = arr;

  Json::FastWriter writer;
  resp->set_body(writer.write(root));
  resp->set_status(RESP_OK);
}

void GetDetailByNameCommand::handle_request(
    const std::shared_ptr<Request>& req) {
  part_number_ = get_part_number_from_regex(req->get_target(), regexpr_,
                                            part_number_group_index_);

  detail_ = DetailsFacade::instanse().get_detail(part_number_);
}

void GetDetailByNameCommand::get_response(
    const std::shared_ptr<Response>& resp) {
  Json::Value root;

  root["part_number"] = detail_.part_number();
  root["name_rus"] = detail_.name_rus();
  root["name_eng"] = detail_.name_eng();
  root["producer_id"] = std::to_string(detail_.producer_id());

  Json::FastWriter writer;
  resp->set_body(writer.write(root));
  resp->set_status(RESP_OK);
}
