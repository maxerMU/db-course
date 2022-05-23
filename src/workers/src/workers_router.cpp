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

  RequestParams login{"/auth/login", POST};
  static_routes[login] =
      std::shared_ptr<BaseCommandCreator>(new CommandCreator<LoginCommand>());

  RequestParams auth{"/auth", GET};
  static_routes[auth] =
      std::shared_ptr<BaseCommandCreator>(new CommandCreator<AuthCommand>());
}
