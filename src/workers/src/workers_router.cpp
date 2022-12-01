#include "workers_router.h"
#include <iostream>

std::shared_ptr<BaseCommand> WorkersRouter::route_req(const std::string& target,
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

WorkersRouter::WorkersRouter() {
  RequestParams worker_post{"/workers", POST};
  static_routes[worker_post] = std::shared_ptr<BaseCommandCreator>(
      new CommandCreator<AddWorkerCommand>());

  RequestParams workers_get{"/workers", GET};
  static_routes[workers_get] = std::shared_ptr<BaseCommandCreator>(
      new CommandCreator<GetWorkersCommand>());

  RequestParams worker_get{"/workers/me", GET};
  static_routes[worker_get] = std::shared_ptr<BaseCommandCreator>(
      new CommandCreator<GetWorkerCommand>());

  RequestParams worker_put{"/workers", PUT};
  static_routes[worker_put] = std::shared_ptr<BaseCommandCreator>(
      new CommandCreator<UpdateWorkerCommand>());

  std::regex get_worker_regex("/workers/([0-9]+)");
  RequestParamsRegEx worker_get_by_id{get_worker_regex, GET};
  dynamic_routes.push_back(dynamic_route_t(
      get_worker_regex,
      std::shared_ptr<BaseCommandCreator>(
          new CommandCreator<GetWorkerByIdCommand>(get_worker_regex, 1))));

  std::regex privilege_regex("/workers/([0-9]+)/privilege");
  RequestParamsRegEx worker_update_privilege{privilege_regex, PATCH};
  dynamic_routes.push_back(dynamic_route_t(
      worker_update_privilege,
      std::shared_ptr<BaseCommandCreator>(
          new CommandCreator<UpdatePrivilegeCommand>(privilege_regex, 1))));

  RequestParams login{"/auth/login", POST};
  static_routes[login] =
      std::shared_ptr<BaseCommandCreator>(new CommandCreator<LoginCommand>());

  RequestParams auth{"/auth", GET};
  static_routes[auth] =
      std::shared_ptr<BaseCommandCreator>(new CommandCreator<AuthCommand>());
}
