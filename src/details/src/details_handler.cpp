#include "details_handler.h"
#include <iostream>
#include "base_exception.h"
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
