#include "details_router.h"
#include <iostream>

std::shared_ptr<BaseCommand> DetailsRouter::route_req(const std::string& target,
                                                      const method_t& method) {
  RequestParams static_params{target, method};
  std::shared_ptr<BaseCommandCreator> creator;

  if (static_routes.contains(static_params))
    creator = static_routes[static_params];

  if (!creator) {
    for (auto dyn_route : dynamic_routes) {
      if (std::regex_match(target, dyn_route.first.target) &&
          method == dyn_route.first.method) {
        creator = dyn_route.second;
        break;
      }
    }
  }

  if (creator)
    return creator->create_command();

  return nullptr;
}

DetailsRouter::DetailsRouter() {
  RequestParams tmp{"/details", GET};
  static_routes[tmp] = std::shared_ptr<BaseCommandCreator>(
      new CommandCreator<GetDetailsCommand>());

  RequestParams tmp1{"/details", POST};
  static_routes[tmp1] = std::shared_ptr<BaseCommandCreator>(
      new CommandCreator<AddDetailCommand>());

  std::regex detail_regex("/details/([a-zA-Z0-9\\-]+)");
  RequestParamsRegEx detail_get_req{detail_regex, GET};
  dynamic_routes.push_back(dynamic_route_t(
      detail_get_req,
      std::shared_ptr<BaseCommandCreator>(
          new CommandCreator<GetDetailByNameCommand>(detail_regex, 1))));

  RequestParamsRegEx detail_update_req{detail_regex, PUT};
  dynamic_routes.push_back(dynamic_route_t(
      detail_update_req,
      std::shared_ptr<BaseCommandCreator>(
          new CommandCreator<UpdateDetailCommand>(detail_regex, 1))));

  RequestParamsRegEx detail_delete_req{detail_regex, DELETE};
  dynamic_routes.push_back(dynamic_route_t(
      detail_delete_req,
      std::shared_ptr<BaseCommandCreator>(
          new CommandCreator<DeleteDetailCommand>(detail_regex, 1))));

  RequestParams tmp3{"/producers", GET};
  static_routes[tmp3] = std::shared_ptr<BaseCommandCreator>(
      new CommandCreator<GetProducersCommand>());

  RequestParams tmp4{"/producers", POST};
  static_routes[tmp4] = std::shared_ptr<BaseCommandCreator>(
      new CommandCreator<AddProducerCommand>());

  std::regex producer_by_id_regex("/producers/([a-zA-Z0-9]*)");
  RequestParamsRegEx tmpregex2{producer_by_id_regex, GET};
  dynamic_routes.push_back(
      dynamic_route_t(tmpregex2, std::shared_ptr<BaseCommandCreator>(
                                     new CommandCreator<GetProducerByIdCommand>(
                                         producer_by_id_regex, 1))));

  RequestParamsRegEx tmpregex3{producer_by_id_regex, DELETE};
  dynamic_routes.push_back(dynamic_route_t(
      tmpregex3,
      std::shared_ptr<BaseCommandCreator>(
          new CommandCreator<DeleteProducerCommand>(producer_by_id_regex, 1))));

  RequestParamsRegEx tmpregex4{producer_by_id_regex, PUT};
  dynamic_routes.push_back(dynamic_route_t(
      tmpregex4,
      std::shared_ptr<BaseCommandCreator>(
          new CommandCreator<UpdateProducerCommand>(producer_by_id_regex, 1))));

  std::regex detail_swaps_regex("/details/([a-zA-Z0-9\\-]+)/swaps");
  RequestParamsRegEx swap_post_req{detail_swaps_regex, POST};
  dynamic_routes.push_back(dynamic_route_t(
      swap_post_req,
      std::shared_ptr<BaseCommandCreator>(
          new CommandCreator<AddDetailSwapCommand>(detail_swaps_regex, 1))));

  RequestParamsRegEx swap_get_req{detail_swaps_regex, GET};
  dynamic_routes.push_back(dynamic_route_t(
      swap_get_req,
      std::shared_ptr<BaseCommandCreator>(
          new CommandCreator<GetDetailSwapsCommand>(detail_swaps_regex, 1))));

  RequestParamsRegEx swap_delete_req{detail_swaps_regex, DELETE};
  dynamic_routes.push_back(dynamic_route_t(
      swap_delete_req,
      std::shared_ptr<BaseCommandCreator>(
          new CommandCreator<DeleteDetailSwapCommand>(detail_swaps_regex, 1))));

  RequestParams stock_post{"/stock", POST};
  static_routes[stock_post] = std::shared_ptr<BaseCommandCreator>(
      new CommandCreator<AddDetailToStockCommand>());

  RequestParams stock_get{"/stock", GET};
  static_routes[stock_get] = std::shared_ptr<BaseCommandCreator>(
      new CommandCreator<DetailsInStockCommand>());

  RequestParams stock_prev{"/stock?previous_details=1", GET};
  static_routes[stock_prev] = std::shared_ptr<BaseCommandCreator>(
      new CommandCreator<DetailsForAllTimeCommand>());

  RequestParams stock_delete{"/stock", DELETE};
  static_routes[stock_delete] = std::shared_ptr<BaseCommandCreator>(
      new CommandCreator<RemoveDetailFromStockCommand>());

  std::regex detail_stock_regex("/stock\\?part_number=([a-zA-Z0-9\\-]+)");
  RequestParamsRegEx stock_read_qty{detail_stock_regex, GET};
  dynamic_routes.push_back(dynamic_route_t(
      stock_read_qty,
      std::shared_ptr<BaseCommandCreator>(
          new CommandCreator<DetailQuantityCommand>(detail_stock_regex, 1))));

  std::regex stock_log_regex(
      "/stock/logs\\?time_start=([0-9\\-]+)&time_end=([0-9\\-]+)");
  RequestParamsRegEx stock_log{stock_log_regex, GET};
  dynamic_routes.push_back(dynamic_route_t(
      stock_log,
      std::shared_ptr<BaseCommandCreator>(
          new CommandCreator<StockLogsCommand>(stock_log_regex, 1, 2))));
}
