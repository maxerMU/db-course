#include "api_gateway_handler.h"
#include <iostream>

ApiGatewayHandler::ApiGatewayHandler(net::io_context &context_)
    : ioc(context_) {}

void ApiGatewayHandler::handle_request(const std::shared_ptr<Request> &req) {
  std::cout << req->get_body() << std::endl;
  std::cout << req->get_target() << std::endl;
}

void ApiGatewayHandler::make_response(const std::shared_ptr<Response> &resp) {
  resp->set_body("{\"name\": \"Max\"}");
}
