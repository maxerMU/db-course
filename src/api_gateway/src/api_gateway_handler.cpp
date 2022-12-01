#include "api_gateway_handler.h"

#include <iostream>

ApiGatewayHandler::ApiGatewayHandler(const std::shared_ptr<BaseConfig>& config)
    : config_(config), cur_adapter_index_(0) {
  set_client_indexes(config);
}

state_t ApiGatewayHandler::handle_request(const std::shared_ptr<Request>& req) {
  cur_request_ = req;
  cur_adapters_ = ApiGatewayRouter::instanse().route_req(req->get_target());
  cur_adapter_index_ = 0;

  if (cur_adapters_.size() == 0) {
    cur_status = RESP_NOT_FOUND;
    return RES_END;
  }

  return RES_CONTINUE;
}

state_t ApiGatewayHandler::get_next_request(std::shared_ptr<Request>& req,
                                            size_t& client_index) {
  cur_adapters_[cur_adapter_index_]->init(cur_request_, client_indexes,
                                          cur_response_);
  auto state =
      cur_adapters_[cur_adapter_index_]->make_request(req, client_index);

  if (state == RES_END) {
    if (++cur_adapter_index_ < cur_adapters_.size()) {
      state = RES_REPEAT;
    }
  }

  return state;
}

state_t ApiGatewayHandler::handle_response(
    const std::shared_ptr<Response>& resp) {
  if (!cur_response_) {
    cur_response_ = resp;
  }

  auto state =
      cur_adapters_[cur_adapter_index_]->handle_response(cur_response_, resp);

  if (state == RES_CONTINUE) {
    cur_adapter_index_++;
  } else if (state == RES_REPEAT) {
    state = RES_CONTINUE;
  }

  if (cur_adapter_index_ >= cur_adapters_.size()) return RES_END;

  return state;
}

void ApiGatewayHandler::make_response(const std::shared_ptr<Response>& resp) {
  if (cur_response_)
    resp->copy(cur_response_);
  else
    resp->set_status(cur_status);
}
