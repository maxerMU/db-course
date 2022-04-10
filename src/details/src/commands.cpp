#include "commands.h"
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>
#include <iostream>
#include "server_exceptions.h"

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
  std::smatch match;

  auto target = req->get_target();
  if (std::regex_search(target, match, regexpr_)) {
    part_number_ = match.str(part_number_group_index_);
    std::cout << part_number_ << std::endl;
  } else {
    throw RegExpParserException(
        "couldn't parse regexpr for DetailSwapsCommand");
  }

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

void AddDetailCommand::handle_request(const std::shared_ptr<Request>& req) {}

void AddDetailCommand::get_response(const std::shared_ptr<Response>& resp) {}
