#include "worker_names_adapter.h"

#include <iostream>
#include <regex>

#include "api_gateway_clients.h"
#include "worker_dto.h"

WorkerNamesAdapter::WorkerNamesAdapter() {}

void WorkerNamesAdapter::init(
    const std::shared_ptr<Request> &req,
    const std::map<std::string, size_t> &client_indexes,
    const std::shared_ptr<Response> &cur_gateway_resp) {
  if (is_initialised) {
    return;
  }

  req_ = req;
  client_indexes_ = client_indexes;

  std::string s = cur_gateway_resp->get_body();
  std::smatch m;

  while (std::regex_search(s, m, worker_id_regexp)) {
    auto worker_id = atol(m.str(1).c_str());
    worker_ids.insert(worker_id);
    s = m.suffix().str();
  }

  is_initialised = true;
}

state_t WorkerNamesAdapter::make_request(std::shared_ptr<Request> &req,
                                         size_t &client_index) {
  if (!worker_ids.size()) {
    return RES_END;
  }

  cur_worker_id = *(worker_ids.begin());
  req->set_target(workers_url + "/" + std::to_string(cur_worker_id));
  req->set_method(GET);
  req->set_headers(req_->get_headers());
  client_index = client_indexes_[WorkersServerName];

  return RES_CONTINUE;
}

state_t WorkerNamesAdapter::handle_response(
    const std::shared_ptr<Response> &cur_gateway_repsonse,
    const std::shared_ptr<Response> &server_response) {
  if (server_response->get_status() != RESP_OK) {
    cur_gateway_repsonse->set_body("");
    cur_gateway_repsonse->set_status(server_response->get_status());
    return RES_END;
  }

  WorkerDto worker(server_response->get_body());
  std::string worker_name = worker.get_name() + " " + worker.get_surname();

  auto regex =
      std::regex(std::string("\"worker_id\":") + std::to_string(cur_worker_id));
  auto res = std::regex_replace(
      cur_gateway_repsonse->get_body(), regex,
      std::string("\"worker\"") + ":\"" + worker_name + "\"");

  cur_gateway_repsonse->set_body(res);

  worker_ids.erase(cur_worker_id);
  return RES_REPEAT;
}
