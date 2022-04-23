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

  // RequestParams tmp2{"/details?in_stock=1", GET};
  // static_routes[tmp2] = std::shared_ptr<BaseCommandCreator>(
  //     new CommandCreator<DetailsInStockCommand>());

  RequestParams tmp3{"/producers", GET};
  static_routes[tmp3] = std::shared_ptr<BaseCommandCreator>(
      new CommandCreator<GetProducersCommand>());

  RequestParams tmp4{"/producers", POST};
  static_routes[tmp4] = std::shared_ptr<BaseCommandCreator>(
      new CommandCreator<AddProducerCommand>());

  // std::regex detail_swaps_regex("/details/([a-zA-Z0-9]*)/swaps");
  // RequestParamsRegEx tmpregex{detail_swaps_regex, GET};
  // dynamic_routes.push_back(dynamic_route_t(
  //     tmpregex,
  //     std::shared_ptr<BaseCommandCreator>(
  //         new CommandCreator<DetailSwapsCommand>(detail_swaps_regex, 1))));

  // RequestParamsRegEx tmpregex1{detail_swaps_regex, POST};
  // dynamic_routes.push_back(dynamic_route_t(
  //     tmpregex1,
  //     std::shared_ptr<BaseCommandCreator>(
  //         new CommandCreator<AddDetailSwapsCommand>(detail_swaps_regex,
  //         1))));

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
}
