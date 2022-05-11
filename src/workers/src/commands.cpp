#include "commands.h"
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>
#include <iostream>
#include "logic_exceptions.h"
#include "server_exceptions.h"

void AddWorkerCommand::handle_request(const std::shared_ptr<Request>& req) {
  WorkerPost worker(req->get_body());
  WorkersFacade::instanse().sign_up(worker);
}

void AddWorkerCommand::get_response(const std::shared_ptr<Response>& resp) {
  resp->set_status(RESP_OK);
}

void LoginCommand::handle_request(const std::shared_ptr<Request>& req) {
  WorkerAuth worker(req->get_body());
  try {
    token_ = WorkersFacade::instanse().login(worker);
  } catch (InvalidAuthDataException& ex) {
    status_code_ = RESP_UNAUTHIRIZED;
  }
}

void LoginCommand::get_response(const std::shared_ptr<Response>& resp) {
  if (status_code_ == RESP_OK) {
    Json::Value root;
    root["access_token"] = token_;

    Json::FastWriter writer;
    resp->set_body(writer.write(root));
    resp->set_status(RESP_OK);
  } else {
    resp->set_status(status_code_);
  }
}
