#include "workers_adapter.h"
#include "api_gateway_clients.h"

void WorkersAdapter::init(const std::shared_ptr<Request>& req,
                          const std::map<std::string, size_t>& client_indexes) {
  req_ = req;
  client_indexes_ = client_indexes;

  is_initialized = true;
}

void WorkersAdapter::make_request(std::shared_ptr<Request>& req,
                                  size_t& client_index) {
  req = req_;
  client_index = client_indexes_[WorkersServerName];
}

state_t WorkersAdapter::handle_response(
    const std::shared_ptr<Response>& cur_gateway_repsonse,
    const std::shared_ptr<Response>& server_response) {
  cur_gateway_repsonse->copy(server_response);
  if (server_response->get_status() == RESP_OK)
    return RES_CONTINUE;

  return RES_END;
}