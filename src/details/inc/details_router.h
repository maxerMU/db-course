#ifndef DETAILSROUTER_H
#define DETAILSROUTER_H

#include <map>
#include <memory>
#include <regex>
#include <vector>
#include "commands.h"

struct RequestParams {
  std::string target;
  method_t method;

  bool operator<(const RequestParams& params) const {
    if (this->target < params.target)
      return true;
    if (this->method < params.method)
      return true;

    return false;
  }
};

struct RequestParamsRegEx {
  std::regex target;
  method_t method;
};

typedef std::pair<RequestParamsRegEx, std::shared_ptr<BaseCommandCreator>>
    dynamic_route_t;

class DetailsRouter {
 public:
  std::shared_ptr<BaseCommand> route_req(const std::string& target,
                                         const method_t& method);

  static DetailsRouter& instanse() {
    static DetailsRouter router;
    return router;
  }

 private:
  DetailsRouter();
  DetailsRouter(DetailsRouter&) = delete;
  std::map<RequestParams, std::shared_ptr<BaseCommandCreator>> static_routes;
  std::vector<dynamic_route_t> dynamic_routes;
};

#endif  // DETAILSROUTER_H
