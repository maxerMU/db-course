#include "api_gateway_router.h"
#include <iostream>
#include "details_adapter.h"
#include "workers_adapter.h"

adapters_t ApiGatewayRouter::route_req(const std::string& target) {
  creators_t creators;
  if (static_routes.contains(target))
    creators = static_routes[target];

  if (creators.empty()) {
    for (auto dyn_route : dynamic_routes) {
      std::cout << target << std::endl;
      if (std::regex_match(target, dyn_route.first)) {
        creators = dyn_route.second;
        break;
      }
    }
  }

  adapters_t adapters;
  for (auto creator : creators) {
    adapters.push_back(creator->create_adapter());
  }

  return adapters;
}

ApiGatewayRouter::ApiGatewayRouter() {
  creators_t tmp;

  tmp.push_back(std::shared_ptr<BaseApiGatewayAdapterCreator>(
      new ApiGatewayAdapterCreator<DetailsAdapter>()));
  static_routes["/details"] = tmp;
  tmp.clear();

  tmp.push_back(std::shared_ptr<BaseApiGatewayAdapterCreator>(
      new ApiGatewayAdapterCreator<DetailsAdapter>()));
  static_routes["/producers"] = tmp;
  tmp.clear();

  tmp.push_back(std::shared_ptr<BaseApiGatewayAdapterCreator>(
      new ApiGatewayAdapterCreator<DetailsAdapter>()));
  static_routes["/stock"] = tmp;
  tmp.clear();

  tmp.push_back(std::shared_ptr<BaseApiGatewayAdapterCreator>(
      new ApiGatewayAdapterCreator<WorkersAdapter>()));
  static_routes["/workers"] = tmp;
  tmp.clear();

  tmp.push_back(std::shared_ptr<BaseApiGatewayAdapterCreator>(
      new ApiGatewayAdapterCreator<WorkersAdapter>()));
  static_routes["/auth/login"] = tmp;
  tmp.clear();

  tmp.push_back(std::shared_ptr<BaseApiGatewayAdapterCreator>(
      new ApiGatewayAdapterCreator<WorkersAdapter>()));
  static_routes["/auth"] = tmp;
  tmp.clear();

  tmp.push_back(std::shared_ptr<BaseApiGatewayAdapterCreator>(
      new ApiGatewayAdapterCreator<DetailsAdapter>()));
  static_routes["/stock?previous_details=1"] = tmp;
  tmp.clear();

  tmp.push_back(std::shared_ptr<BaseApiGatewayAdapterCreator>(
      new ApiGatewayAdapterCreator<DetailsAdapter>()));
  std::regex stock_regex("/stock\\?.*");
  dynamic_routes.push_back(std::pair<std::regex, creators_t>(stock_regex, tmp));
  tmp.clear();

  tmp.push_back(std::shared_ptr<BaseApiGatewayAdapterCreator>(
      new ApiGatewayAdapterCreator<DetailsAdapter>()));
  std::regex detail_swaps_regex("/details/([a-zA-Z0-9\\-]+)/swaps");
  dynamic_routes.push_back(
      std::pair<std::regex, creators_t>(detail_swaps_regex, tmp));
  tmp.clear();

  tmp.push_back(std::shared_ptr<BaseApiGatewayAdapterCreator>(
      new ApiGatewayAdapterCreator<DetailsAdapter>()));
  std::regex detail_regex("/details/([a-zA-Z0-9\\-]+)");
  dynamic_routes.push_back(
      std::pair<std::regex, creators_t>(detail_regex, tmp));
  tmp.clear();

  tmp.push_back(std::shared_ptr<BaseApiGatewayAdapterCreator>(
      new ApiGatewayAdapterCreator<DetailsAdapter>()));
  std::regex producer_by_id_regex("/producers/([a-zA-Z0-9]*)");
  dynamic_routes.push_back(
      std::pair<std::regex, creators_t>(producer_by_id_regex, tmp));
  tmp.clear();
}
