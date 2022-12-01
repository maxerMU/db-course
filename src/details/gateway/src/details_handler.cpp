#include "details_handler.h"

#include <iostream>

#include "base_exception.h"
#include "database_exceptions.h"
#include "details_clients.h"
#include "details_router.h"

DetailsHandler::DetailsHandler(const std::shared_ptr<BaseConfig>& config)
    : cur_status_(RESP_OK) {}

void DetailsHandler::handle_request(const std::shared_ptr<Request>& req) {
  command_ =
      DetailsRouter::instanse().route_req(req->get_target(), req->get_method());

  if (!command_) {
    cur_status_ = RESP_NOT_FOUND;
    return;
  }

  try {
    command_->handle_request(req);
  } catch (DatabaseNotFoundException& ex) {
    cur_status_ = RESP_NOT_FOUND;
  } catch (std::exception& ex) {
    exception_description_ = ex.what();
    cur_status_ = RESP_INTERNAL_SERVER_ERROR;
  }
}

void DetailsHandler::make_response(const std::shared_ptr<Response>& resp) {
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

DetailsAuthHandler::DetailsAuthHandler(
    const std::shared_ptr<BaseConfig>& config) {
  set_client_indexes(config);
}

state_t DetailsAuthHandler::handle_request(
    const std::shared_ptr<Request>& req) {
  cur_request_ = req;
  command_ =
      DetailsRouter::instanse().route_req(req->get_target(), req->get_method());

  if (!command_) {
    cur_status_ = RESP_NOT_FOUND;
    return RES_END;
  }

  return RES_CONTINUE;
}

state_t DetailsAuthHandler::get_next_request(std::shared_ptr<Request>& req,
                                             size_t& client_index) {
  req->copy(cur_request_);
  req->set_target(AuthTarget);
  req->set_method(AuthMethod);
  req->set_body(make_privilege_json(command_->get_min_privilege_level()));
  client_index = client_indexes[AuthServerName];

  return RES_CONTINUE;
}

state_t DetailsAuthHandler::handle_response(
    const std::shared_ptr<Response>& resp) {
  cur_status_ = resp->get_status();
  if (cur_status_ != RESP_OK) {
    return RES_END;
  }

  try {
    ExtraData data(resp->get_body());
    cur_request_->set_extra_data(data);
    std::cout << resp->get_body() << std::endl;

    command_->handle_request(cur_request_);
    cur_status_ = RESP_OK;
  } catch (DatabaseNotFoundException& ex) {
    cur_status_ = RESP_NOT_FOUND;

  } catch (std::exception& ex) {
    exception_description_ = ex.what();
    cur_status_ = RESP_INTERNAL_SERVER_ERROR;
  }

  return RES_END;
}

void DetailsAuthHandler::make_response(const std::shared_ptr<Response>& resp) {
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
