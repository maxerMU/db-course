#include "dummy_server_handler.h"
#include <chrono>
#include <iostream>
#include <thread>

DummyServerHandler::DummyServerHandler(
    const std::shared_ptr<BaseConfig>& config) {
  append_string = config->get_string_field({"AppendString"});
}

void DummyServerHandler::handle_request(const std::shared_ptr<Request>& req) {
  std::cout << req->get_body() << std::endl;
  std::cout << req->get_target() << std::endl;
  req_body = req->get_body();

  if (req->get_target() == "/test1") {
    res = req_body + append_string;
  } else if (req->get_target() == "/test2") {
    res = req_body + append_string;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

void DummyServerHandler::make_response(const std::shared_ptr<Response>& resp) {
  resp->set_body(res);
}
