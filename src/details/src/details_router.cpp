#include "details_router.h"

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
      new CommandCreator<DetailsForAllTimeCommand>());

  RequestParams tmp1{"/details_in_stock", GET};
  static_routes[tmp1] = std::shared_ptr<BaseCommandCreator>(
      new CommandCreator<DetailsInStockCommand>());

  std::regex detail_swaps_regex("/detail_swaps\\?part_number=(.*)");
  RequestParamsRegEx tmpregex{detail_swaps_regex, GET};
  dynamic_routes.push_back(dynamic_route_t(
      tmpregex,
      std::shared_ptr<BaseCommandCreator>(
          new CommandCreator<DetailSwapsCommand>(detail_swaps_regex, 1))));
}
