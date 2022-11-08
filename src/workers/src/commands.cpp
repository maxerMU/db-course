#include "commands.h"
#include <iostream>
#include "converters.h"
#include "logic_exceptions.h"
#include "server_exceptions.h"

size_t get_worker_id_from_regex(const std::string& target,
                                const std::regex& regexpr,
                                size_t worker_id_group_index) {
  std::smatch match;
  std::string worker_id_str;
  if (std::regex_search(target, match, regexpr)) {
    worker_id_str = match.str(worker_id_group_index);
  } else {
    throw RegExpParserException("couldn't parse regexpr for worker id");
  }

  size_t worker_id;
  try {
    worker_id = std::stoll(worker_id_str);
  } catch (std::exception) {
    throw RegExpParserException("couldn't convert " + worker_id_str +
                                " to size_t");
  }

  return worker_id;
}

PrivilegeLevel parse_privilege_level(const std::string& json_str) {
  if (json_str.empty()) {
    return CLIENT;
  }
  Json::Value value;
  Json::Reader reader;

  bool parse_successfull = reader.parse(json_str, value);

  if (!parse_successfull) {
    throw JsonParserException("can't parse WorkerAuth object");
  }

  auto privilege = value["privilege_level"].asInt();

  return (PrivilegeLevel)privilege;
}

void AddWorkerCommand::handle_request(const std::shared_ptr<Request>& req) {
  WorkerPost worker(req->get_body());
  worker_id = WorkersFacade::instanse().sign_up(worker);
}

void AddWorkerCommand::get_response(const std::shared_ptr<Response>& resp) {
  Json::Value root;
  root["worker_id"] = (int)worker_id;

  Json::FastWriter writer;
  resp->set_body(writer.write(root));
  resp->set_status(RESP_OK);
}

PrivilegeLevel AddWorkerCommand::get_min_privilege_level() {
  return GUEST;
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

PrivilegeLevel LoginCommand::get_min_privilege_level() {
  return GUEST;
}

void AuthCommand::handle_request(const std::shared_ptr<Request>& req) {
  auto headers_ = req->get_headers();
  token_ = "";
  for (auto header : headers_) {
    if (header.first == "Autharization" || header.first == "autharization") {
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

  auto privilege = parse_privilege_level(req->get_body());
  is_valid = WorkersFacade::instanse().is_valid_access(worker_id_, privilege);
  if (!is_valid) {
    status_code_ = RESP_FORBIDDEN;
    return;
  } else {
    status_code_ = RESP_OK;
  }
}

void AuthCommand::get_response(const std::shared_ptr<Response>& resp) {
  if (status_code_ == RESP_OK) {
    Json::Value root;
    root["worker_id"] = (unsigned long long)worker_id_;

    Json::FastWriter writer;
    resp->set_body(writer.write(root));
    resp->set_status(RESP_OK);
  } else {
    resp->set_status(status_code_);
  }
}

PrivilegeLevel AuthCommand::get_min_privilege_level() {
  return GUEST;
}

void GetWorkerCommand::handle_request(const std::shared_ptr<Request>& req) {
  auto worker_id = req->get_extra_data().auth_inf.worker_id;
  worker_ = WorkersFacade::instanse().get_worker(worker_id);
}

void GetWorkerCommand::get_response(const std::shared_ptr<Response>& resp) {
  resp->set_body(to_json(worker_));
  resp->set_status(RESP_OK);
}

PrivilegeLevel GetWorkerCommand::get_min_privilege_level() {
  return CLIENT;
}

void UpdateWorkerCommand::handle_request(const std::shared_ptr<Request>& req) {
  WorkerPost worker_post(req->get_body());
  WorkerUpdate worker_update(req->get_extra_data().auth_inf.worker_id,
                             worker_post);
  WorkersFacade::instanse().update_worker(worker_update);
}

void UpdateWorkerCommand::get_response(const std::shared_ptr<Response>& resp) {
  resp->set_status(RESP_OK);
}

PrivilegeLevel UpdateWorkerCommand::get_min_privilege_level() {
  return CLIENT;
}
void UpdatePrivilegeCommand::handle_request(
    const std::shared_ptr<Request>& req) {
  auto worker_id = get_worker_id_from_regex(req->get_target(), regexpr_,
                                            worker_id_group_index_);
  auto privilege = parse_privilege_level(req->get_body());

  WorkersFacade::instanse().update_worker_privilege(worker_id, privilege);
}

void UpdatePrivilegeCommand::get_response(
    const std::shared_ptr<Response>& resp) {
  resp->set_status(RESP_OK);
}

PrivilegeLevel UpdatePrivilegeCommand::get_min_privilege_level() {
  return ADMIN;
}

void GetWorkerByIdCommand::handle_request(const std::shared_ptr<Request>& req) {
  auto worker_id = get_worker_id_from_regex(req->get_target(), regexpr_,
                                            worker_id_group_index_);

  worker_ = WorkersFacade::instanse().get_worker(worker_id);
}

void GetWorkerByIdCommand::get_response(const std::shared_ptr<Response>& resp) {
  resp->set_body(to_json(worker_));
  resp->set_status(RESP_OK);
}

PrivilegeLevel GetWorkerByIdCommand::get_min_privilege_level() {
  return CLIENT;
}

void GetWorkersCommand::handle_request(const std::shared_ptr<Request>& req) {
  workers_ = WorkersFacade::instanse().get_workers();
}

void GetWorkersCommand::get_response(const std::shared_ptr<Response>& resp) {
  resp->set_body(to_json(workers_));
  resp->set_status(RESP_OK);
}

PrivilegeLevel GetWorkersCommand::get_min_privilege_level() {
  return CLIENT;
}
