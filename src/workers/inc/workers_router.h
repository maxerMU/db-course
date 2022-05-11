#ifndef WORKERSROUTER_H
#define WORKERSROUTER_H

#include <map>
#include <memory>
#include <regex>
#include <vector>
#include "commands.h"

struct RequestParams {
  std::string target;
  method_t method;

  bool operator<(const RequestParams& params) const {
    return target < params.target ||
           (target == params.target && method < params.method);
  }
};

struct RequestParamsRegEx {
  std::regex target;
  method_t method;
};

typedef std::pair<RequestParamsRegEx, std::shared_ptr<BaseCommandCreator>>
    dynamic_route_t;

class WorkersRouter {
 public:
  std::shared_ptr<BaseCommand> route_req(const std::string& target,
                                         const method_t& method);

  static WorkersRouter& instanse() {
    static WorkersRouter router;
    return router;
  }

 private:
  WorkersRouter();
  WorkersRouter(WorkersRouter&) = delete;
  std::map<RequestParams, std::shared_ptr<BaseCommandCreator>> static_routes;
  std::vector<dynamic_route_t> dynamic_routes;
};

#endif  // WORKERSROUTER_H
