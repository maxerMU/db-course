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
  details_names_ = DetailsFacade::instanse().get_prev_details_in_stock();
}

void DetailsForAllTimeCommand::get_response(
    const std::shared_ptr<Response>& resp) {
  Json::Value arr = Json::arrayValue;
  for (auto name : details_names_) {
    Json::Value root;
    root["part_number"] = name;
    arr.append(root);
  }

  Json::Value root;
  root["details"] = arr;

  Json::FastWriter writer;
  resp->set_body(writer.write(root));
  resp->set_status(RESP_OK);
}

void DetailsInStockCommand::handle_request(
    const std::shared_ptr<Request>& req) {
  details_quantities_ = DetailsFacade::instanse().get_details_in_stock();
}

void DetailsInStockCommand::get_response(
    const std::shared_ptr<Response>& resp) {
  Json::Value arr = Json::arrayValue;
  for (auto detail_quantity : details_quantities_) {
    Json::Value root;
    root["part_number"] = detail_quantity.first;
    root["quantity"] = std::to_string(detail_quantity.second);
    arr.append(root);
  }

  Json::Value root;
  root["details"] = arr;

  Json::FastWriter writer;
  resp->set_body(writer.write(root));
  resp->set_status(RESP_OK);
}

void AddDetailCommand::handle_request(const std::shared_ptr<Request>& req) {
  auto detail = Detail(req->get_body());

  DetailsFacade::instanse().add_detail(detail);
}

void AddDetailCommand::get_response(const std::shared_ptr<Response>& resp) {
  resp->set_status(RESP_OK);
}

void AddDetailSwapCommand::handle_request(const std::shared_ptr<Request>& req) {
  part_number_ = get_part_number_from_regex(req->get_target(), regexpr_,
                                            part_number_group_index_);

  Json::Value val;
  Json::Reader reader;

  bool parse_successfull = reader.parse(req->get_body(), val);

  if (!parse_successfull) {
    throw JsonParserException("can't parse add detail swaps request");
  }

  auto part_dst = val["swap_part_numbers"].asString();

  DetailsFacade::instanse().add_detail_swap(part_number_, part_dst);
}

void AddDetailSwapCommand::get_response(const std::shared_ptr<Response>& resp) {
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

void UpdateDetailCommand::handle_request(const std::shared_ptr<Request>& req) {
  auto part_number_ = get_part_number_from_regex(req->get_target(), regexpr_,
                                                 part_number_group_index_);
  detail_ = Detail(part_number_, req->get_body());
  DetailsFacade::instanse().update_detail(detail_);
}

void UpdateDetailCommand::get_response(const std::shared_ptr<Response>& resp) {
  resp->set_status(RESP_OK);
}

void DeleteDetailCommand::handle_request(const std::shared_ptr<Request>& req) {
  auto part_name = get_part_number_from_regex(req->get_target(), regexpr_,
                                              part_number_group_index_);

  DetailsFacade::instanse().delete_detail(part_name);
}

void DeleteDetailCommand::get_response(const std::shared_ptr<Response>& resp) {
  resp->set_status(RESP_OK);
}

void DeleteDetailSwapCommand::handle_request(
    const std::shared_ptr<Request>& req) {
  part_number_ = get_part_number_from_regex(req->get_target(), regexpr_,
                                            part_number_group_index_);

  Json::Value val;
  Json::Reader reader;

  bool parse_successfull = reader.parse(req->get_body(), val);

  if (!parse_successfull) {
    throw JsonParserException("can't parse add detail swaps request");
  }

  auto part_dst = val["swap_part_numbers"].asString();

  DetailsFacade::instanse().delete_detail_swap(part_number_, part_dst);
}

void DeleteDetailSwapCommand::get_response(
    const std::shared_ptr<Response>& resp) {
  resp->set_status(RESP_OK);
}

void GetDetailSwapsCommand::handle_request(
    const std::shared_ptr<Request>& req) {
  auto part_number = get_part_number_from_regex(req->get_target(), regexpr_,
                                                part_number_group_index_);

  details_ = DetailsFacade::instanse().get_detail_swaps(part_number);
}

void GetDetailSwapsCommand::get_response(
    const std::shared_ptr<Response>& resp) {
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

void AddDetailToStockCommand::handle_request(
    const std::shared_ptr<Request>& req) {
  Json::Value value;
  Json::Reader reader;

  bool parse_successfull = reader.parse(req->get_body(), value);

  if (!parse_successfull) {
    throw JsonParserException("can't parse request data");
  }

  std::string part_number = value["part_number"].asString();
  size_t worker_id = value["worker_id"].asUInt64();
  size_t quantity = value["quantity"].asUInt64();

  DetailsFacade::instanse().add_detail_to_stock(part_number, worker_id,
                                                quantity);
}

void AddDetailToStockCommand::get_response(
    const std::shared_ptr<Response>& resp) {
  resp->set_status(RESP_OK);
}

void RemoveDetailFromStockCommand::handle_request(
    const std::shared_ptr<Request>& req) {
  Json::Value value;
  Json::Reader reader;

  bool parse_successfull = reader.parse(req->get_body(), value);

  if (!parse_successfull) {
    throw JsonParserException("can't parse request data");
  }

  std::string part_number = value["part_number"].asString();
  size_t worker_id = value["worker_id"].asUInt64();
  size_t quantity = value["quantity"].asUInt64();

  DetailsFacade::instanse().remove_detail_from_stock(part_number, worker_id,
                                                     quantity);
}

void RemoveDetailFromStockCommand::get_response(
    const std::shared_ptr<Response>& resp) {
  resp->set_status(RESP_OK);
}

void DetailQuantityCommand::handle_request(
    const std::shared_ptr<Request>& req) {
  auto part_number = get_part_number_from_regex(req->get_target(), regexpr_,
                                                part_number_group_index_);

  res = DetailsFacade::instanse().get_detail_in_stock(part_number);
}

void DetailQuantityCommand::get_response(
    const std::shared_ptr<Response>& resp) {
  Json::Value root;
  root["part_number"] = res.first;
  root["quantity"] = std::to_string(res.second);

  Json::FastWriter writer;
  resp->set_body(writer.write(root));
  resp->set_status(RESP_OK);
}
