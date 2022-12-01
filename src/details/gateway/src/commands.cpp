#include "commands.h"

#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>

#include <iostream>

#include "converters.h"
#include "detail_dto.h"
#include "detail_to_stock_dto.h"
#include "get_stock_log_dto.h"
#include "producer_data_dto.h"
#include "server_exceptions.h"
#include "swaps_part_name_dto.h"

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

std::string get_string_from_regex(const std::string& target,
                                  const std::regex& regexpr,
                                  size_t group_index) {
  std::smatch match;

  std::string res;
  if (std::regex_search(target, match, regexpr)) {
    res = match.str(group_index);
  } else {
    throw RegExpParserException("couldn't parse regexpr");
  }

  return res;
}

void DetailsForAllTimeCommand::handle_request(
    const std::shared_ptr<Request>& req) {
  details_names_ = DetailsFacade::instanse().get_prev_details_in_stock();
}

void DetailsForAllTimeCommand::get_response(
    const std::shared_ptr<Response>& resp) {
  resp->set_body(PartNamesArrayConverter().to_json(details_names_));
  resp->set_status(RESP_OK);
}

PrivilegeLevel DetailsForAllTimeCommand::get_min_privilege_level() {
  return SELLER;
}

void DetailsInStockCommand::handle_request(
    const std::shared_ptr<Request>& req) {
  details = DetailsFacade::instanse().get_details_in_stock();
}

void DetailsInStockCommand::get_response(
    const std::shared_ptr<Response>& resp) {
  resp->set_body(StockDetailsConverter().to_json(details));
  resp->set_status(RESP_OK);
}

void AddDetailCommand::handle_request(const std::shared_ptr<Request>& req) {
  auto detail = DetailDto(req->get_body());

  DetailsFacade::instanse().add_detail(detail);
}

void AddDetailCommand::get_response(const std::shared_ptr<Response>& resp) {
  resp->set_status(RESP_OK);
}

void AddDetailSwapCommand::handle_request(const std::shared_ptr<Request>& req) {
  part_number_ = get_string_from_regex(req->get_target(), regexpr_,
                                       part_number_group_index_);

  auto swaps_part_name_dto = SwapsPartNameDto(req->get_body());

  DetailsFacade::instanse().add_detail_swap(part_number_,
                                            swaps_part_name_dto.get_part_dst());
}

void AddDetailSwapCommand::get_response(const std::shared_ptr<Response>& resp) {
  resp->set_status(RESP_OK);
}

void GetProducersCommand::handle_request(const std::shared_ptr<Request>& req) {
  producers_ = DetailsFacade::instanse().get_producers();
}

void GetProducersCommand::get_response(const std::shared_ptr<Response>& resp) {
  resp->set_body(ProducersArrayConverter().to_json(producers_));
  resp->set_status(RESP_OK);
}

void AddProducerCommand::handle_request(const std::shared_ptr<Request>& req) {
  auto producer = ProducerDataDto(req->get_body());

  id_ = DetailsFacade::instanse().add_producer(producer);
}

void AddProducerCommand::get_response(const std::shared_ptr<Response>& resp) {
  resp->set_body(IdConverter().to_json(id_));
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
  resp->set_body(ProducerConverter().to_json(producer_));
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

  ProducerDataDto producer_data(req->get_body());

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
  resp->set_body(DetailsArrayConverter().to_json(details_));
  resp->set_status(RESP_OK);
}

void GetDetailByNameCommand::handle_request(
    const std::shared_ptr<Request>& req) {
  part_number_ = get_string_from_regex(req->get_target(), regexpr_,
                                       part_number_group_index_);

  detail_ = DetailsFacade::instanse().get_detail(part_number_);
}

void GetDetailByNameCommand::get_response(
    const std::shared_ptr<Response>& resp) {
  resp->set_body(DetailConverter().to_json(detail_));
  resp->set_status(RESP_OK);
}

void UpdateDetailCommand::handle_request(const std::shared_ptr<Request>& req) {
  auto part_number_ = get_string_from_regex(req->get_target(), regexpr_,
                                            part_number_group_index_);
  detail_ = DetailDto(part_number_, req->get_body());
  DetailsFacade::instanse().update_detail(detail_);
}

void UpdateDetailCommand::get_response(const std::shared_ptr<Response>& resp) {
  resp->set_status(RESP_OK);
}

void DeleteDetailCommand::handle_request(const std::shared_ptr<Request>& req) {
  auto part_name = get_string_from_regex(req->get_target(), regexpr_,
                                         part_number_group_index_);

  DetailsFacade::instanse().delete_detail(part_name);
}

void DeleteDetailCommand::get_response(const std::shared_ptr<Response>& resp) {
  resp->set_status(RESP_OK);
}

void DeleteDetailSwapCommand::handle_request(
    const std::shared_ptr<Request>& req) {
  part_number_ = get_string_from_regex(req->get_target(), regexpr_,
                                       part_number_group_index_);

  auto swaps_part_name_dto = SwapsPartNameDto(req->get_body());

  DetailsFacade::instanse().delete_detail_swap(
      part_number_, swaps_part_name_dto.get_part_dst());
}

void DeleteDetailSwapCommand::get_response(
    const std::shared_ptr<Response>& resp) {
  resp->set_status(RESP_OK);
}

void GetDetailSwapsCommand::handle_request(
    const std::shared_ptr<Request>& req) {
  auto part_number = get_string_from_regex(req->get_target(), regexpr_,
                                           part_number_group_index_);

  details_ = DetailsFacade::instanse().get_detail_swaps(part_number);
}

void GetDetailSwapsCommand::get_response(
    const std::shared_ptr<Response>& resp) {
  resp->set_body(DetailsArrayConverter().to_json(details_));
  resp->set_status(RESP_OK);
}

void AddDetailToStockCommand::handle_request(
    const std::shared_ptr<Request>& req) {
  size_t worker_id = req->get_extra_data().auth_inf.worker_id;

  auto detail_to_stock_dto = DetailToStockDto(req->get_body());

  DetailsFacade::instanse().add_detail_to_stock(
      detail_to_stock_dto.get_part_number(), worker_id,
      detail_to_stock_dto.get_quantity());
}

void AddDetailToStockCommand::get_response(
    const std::shared_ptr<Response>& resp) {
  resp->set_status(RESP_OK);
}

void RemoveDetailFromStockCommand::handle_request(
    const std::shared_ptr<Request>& req) {
  size_t worker_id = req->get_extra_data().auth_inf.worker_id;

  auto detail_to_stock_dto = DetailToStockDto(req->get_body());

  DetailsFacade::instanse().remove_detail_from_stock(
      detail_to_stock_dto.get_part_number(), worker_id,
      detail_to_stock_dto.get_quantity());
}

void RemoveDetailFromStockCommand::get_response(
    const std::shared_ptr<Response>& resp) {
  resp->set_status(RESP_OK);
}

PrivilegeLevel RemoveDetailFromStockCommand::get_min_privilege_level() {
  return STOREKEEPER;
}

void DetailQuantityCommand::handle_request(
    const std::shared_ptr<Request>& req) {
  auto part_number = get_string_from_regex(req->get_target(), regexpr_,
                                           part_number_group_index_);

  res = DetailsFacade::instanse().get_detail_in_stock(part_number);
}

void DetailQuantityCommand::get_response(
    const std::shared_ptr<Response>& resp) {
  resp->set_body(DetailQuantityConverter().to_json(res));
  resp->set_status(RESP_OK);
}

PrivilegeLevel DetailQuantityCommand::get_min_privilege_level() {
  return STOREKEEPER;
}

PrivilegeLevel GetDetailsCommand::get_min_privilege_level() { return GUEST; }

PrivilegeLevel GetDetailByNameCommand::get_min_privilege_level() {
  return GUEST;
}

PrivilegeLevel AddDetailCommand::get_min_privilege_level() { return SELLER; }

PrivilegeLevel UpdateDetailCommand::get_min_privilege_level() { return SELLER; }

PrivilegeLevel DeleteDetailCommand::get_min_privilege_level() { return SELLER; }

PrivilegeLevel GetProducersCommand::get_min_privilege_level() { return GUEST; }

PrivilegeLevel GetProducerByIdCommand::get_min_privilege_level() {
  return GUEST;
}

PrivilegeLevel DeleteProducerCommand::get_min_privilege_level() {
  return SELLER;
}

PrivilegeLevel UpdateProducerCommand::get_min_privilege_level() {
  return SELLER;
}

PrivilegeLevel AddProducerCommand::get_min_privilege_level() { return SELLER; }

PrivilegeLevel AddDetailSwapCommand::get_min_privilege_level() {
  return SELLER;
}

PrivilegeLevel GetDetailSwapsCommand::get_min_privilege_level() {
  return GUEST;
}

PrivilegeLevel DeleteDetailSwapCommand::get_min_privilege_level() {
  return SELLER;
}

PrivilegeLevel AddDetailToStockCommand::get_min_privilege_level() {
  return STOREKEEPER;
}

PrivilegeLevel DetailsInStockCommand::get_min_privilege_level() {
  return SELLER;
}

void StockLogsCommand::handle_request(const std::shared_ptr<Request>& req) {
  std::string time_start = get_string_from_regex(req->get_target(), regexpr_,
                                                 time_start_group_index_);
  std::string time_end =
      get_string_from_regex(req->get_target(), regexpr_, time_end_group_index_);

  stock_logs_ = DetailsFacade::instanse().get_logs(time_start, time_end);
}

void StockLogsCommand::get_response(const std::shared_ptr<Response>& resp) {
  resp->set_body(StockLogsConverter().to_json(stock_logs_));
  resp->set_status(RESP_OK);
}

PrivilegeLevel StockLogsCommand::get_min_privilege_level() { return ADMIN; }
