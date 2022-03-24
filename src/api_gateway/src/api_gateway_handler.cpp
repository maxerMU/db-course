#include "api_gateway_handler.h"
#include <iostream>

ApiGatewayHandler::ApiGatewayHandler(net::io_context &context_)
    : ioc(context_) {}

void ApiGatewayHandler::handle_request(const std::shared_ptr<Request> &req) {
  std::cout << req->get_body() << std::endl;
  std::cout << req->get_target() << std::endl;
}

std::shared_ptr<Response> ApiGatewayHandler::get_response() {
  std::shared_ptr<Response> res = std::make_shared<Response>();

  res->set_body("{\"name\": \"Deniska\"}");

  return res;
}
