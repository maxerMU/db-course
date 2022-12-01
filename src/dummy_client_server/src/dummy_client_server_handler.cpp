#include "dummy_client_server_handler.h"

DummyClientServerHandler::DummyClientServerHandler(
    const std::shared_ptr<BaseConfig> &config)
    : config_(config) {}

state_t DummyClientServerHandler::handle_request(
    const std::shared_ptr<Request> &req) {
  cur_body = req->get_body();

  state_ = REQ_HANDLED;

  return RES_CONTINUE;
}

state_t DummyClientServerHandler::get_next_request(
    std::shared_ptr<Request> &req, size_t &client_index) {
  req->set_body(cur_body);
  req->set_method(GET);
  req->set_target("/test");

  if (state_ == REQ_HANDLED) {
    client_index = 0;
  } else if (state_ == DUMMY1) {
    client_index = 1;
  } else {
    throw std::exception();
  }

  return RES_CONTINUE;
}

state_t DummyClientServerHandler::handle_response(
    const std::shared_ptr<Response> &resp) {
  cur_body = resp->get_body();

  if (state_ == REQ_HANDLED) {
    state_ = DUMMY1;
    return RES_CONTINUE;
  } else if (state_ == DUMMY1) {
    state_ = DUMMY2;
    return RES_END;
  }

  throw std::exception();
}

void DummyClientServerHandler::make_response(
    const std::shared_ptr<Response> &resp) {
  resp->set_body(cur_body);
  resp->set_status(200);
}
