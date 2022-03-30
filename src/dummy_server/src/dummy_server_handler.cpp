#include "dummy_server_handler.h"
#include <iostream>

DummyServerHandler::DummyServerHandler(
    net::io_context &context_, const std::shared_ptr<BaseConfig> &config)
    : ioc(context_) {
  append_string = config->get_string_field({"AppendString"});
}

void DummyServerHandler::handle_request(const std::shared_ptr<Request> &req) {
  std::cout << req->get_body() << std::endl;
  std::cout << req->get_target() << std::endl;
  req_body = req->get_body();
}

void DummyServerHandler::make_response(const std::shared_ptr<Response> &resp) {
  std::string res = req_body + append_string;
  resp->set_body(res);
}
