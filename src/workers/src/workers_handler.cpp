#include "workers_handler.h"
#include <iostream>
#include "base_exception.h"
#include "beast_req.h"
#include "beast_resp.h"
#include "workers_router.h"

WorkersHandler::WorkersHandler(const std::shared_ptr<BaseConfig>& config)
    : cur_status_(RESP_OK) {}

void WorkersHandler::handle_request(const std::shared_ptr<Request>& req) {
  command_ =
      WorkersRouter::instanse().route_req(req->get_target(), req->get_method());

  if (!command_) {
    cur_status_ = RESP_NOT_FOUND;
    return;
  }

  if (command_->need_auth()) {
    ExtraData data;
    cur_status_ = make_auth(data, req);
    if (cur_status_ == RESP_OK)
      req->set_extra_data(data);
    else
      return;
  }

  try {
    command_->handle_request(req);
  } catch (std::exception& ex) {
    exception_description_ = ex.what();
    cur_status_ = RESP_INTERNAL_SERVER_ERROR;
  }
}

void WorkersHandler::make_response(const std::shared_ptr<Response>& resp) {
  if (cur_status_ != RESP_OK) {
    resp->set_status(cur_status_);
    resp->set_body(exception_description_);
    return;
  }

  try {
    command_->get_response(resp);
  } catch (std::exception& ex) {
    exception_description_ = ex.what();
    cur_status_ = RESP_INTERNAL_SERVER_ERROR;
  }

  if (cur_status_ != RESP_OK) {
    resp->set_status(cur_status_);
    resp->set_body(exception_description_);
  }
}

int WorkersHandler::make_auth(ExtraData& data,
                              const std::shared_ptr<Request>& req) {
  std::shared_ptr<Response> resp = std::shared_ptr<Response>(new BeastResp());
  std::shared_ptr<Request> auth_req = std::shared_ptr<Request>(new BeastReq());
  auth_req->copy(req);
  auth_req->set_body(make_privilege_json(command_->get_min_privilege_level()));
  AuthCommand command;
  int result = RESP_OK;
  try {
    command.handle_request(auth_req);
    command.get_response(resp);
    if (resp->get_status() != RESP_OK)
      return resp->get_status();
    data = ExtraData(resp->get_body());
  } catch (std::exception& ex) {
    exception_description_ = ex.what();
    result = RESP_INTERNAL_SERVER_ERROR;
  }

  return result;
}
