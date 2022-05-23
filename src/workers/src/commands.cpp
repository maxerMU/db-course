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

void AuthCommand::handle_request(const std::shared_ptr<Request>& req) {
  auto headers_ = req->get_headers();
  token_ = "";
  for (auto header : headers_) {
    if (header.first == "Autharization") {
      token_ = header.second;
      break;
    }
  }

  if (token_.empty()) {
    status_code_ = RESP_UNAUTHIRIZED;
    return;
  }

  bool is_valid =
      WorkersFacade::instanse().is_valid_session(worker_id_, token_);
  if (!is_valid) {
    status_code_ = RESP_UNAUTHIRIZED;
    return;
  } else {
    status_code_ = RESP_OK;
  }

  // Json::Value value;
  // Json::Reader reader;

  // bool parse_successfull = reader.parse(json_str, value);

  // if (!parse_successfull) {
  //   throw JsonParserException("can't parse WorkerAuth object");
  // }

  // username_ = value["username"].asString();
  // password_ = value["password"].asString();
}

void AuthCommand::get_response(const std::shared_ptr<Response>& resp) {
  if (status_code_ == RESP_OK) {
    Json::Value root;
    root["worker_id"] = std::to_string(worker_id_);

    Json::FastWriter writer;
    resp->set_body(writer.write(root));
    resp->set_status(RESP_OK);
  } else {
    resp->set_status(status_code_);
  }
}
