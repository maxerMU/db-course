#ifndef APIGATEWAYROUTER_H
#define APIGATEWAYROUTER_H

#include <base_api_gateway_adapter.h>
#include <map>
#include <memory>
#include <regex>
#include <vector>

typedef std::vector<std::shared_ptr<BaseApiGatewayAdapter>> adapters_t;
typedef std::vector<std::shared_ptr<BaseApiGatewayAdapterCreator>> creators_t;

class ApiGatewayRouter {
 public:
  adapters_t route_req(const std::string& target);

  static ApiGatewayRouter& instanse() {
    static ApiGatewayRouter router;
    return router;
  }

 private:
  ApiGatewayRouter();
  ApiGatewayRouter(ApiGatewayRouter&) = delete;
  std::map<std::string, creators_t> static_routes;
  std::vector<std::pair<std::regex, creators_t>> dynamic_routes;
};

#endif  // APIGATEWAYROUTER_H
