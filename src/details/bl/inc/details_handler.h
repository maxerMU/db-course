#ifndef DETAILSHANDLER_H
#define DETAILSHANDLER_H

#include "base_config.h"
#include "client_server_req_handler.h"
#include "commands.h"
#include "net.h"
#include "server_req_handler.h"

#define AuthTarget "/auth"
#define AuthMethod GET

class DetailsHandler : public ServerReqHandler {
 public:
  DetailsHandler(const std::shared_ptr<BaseConfig>& config);

  virtual void handle_request(const std::shared_ptr<Request>& req) override;
  virtual void make_response(const std::shared_ptr<Response>& resp) override;

 private:
  int cur_status_;
  std::string exception_description_;
  std::shared_ptr<BaseCommand> command_;
};

class DetailsAuthHandler : public ClientServerReqHandler {
 public:
  DetailsAuthHandler(const std::shared_ptr<BaseConfig>& config);
  virtual state_t handle_request(const std::shared_ptr<Request>& req) override;
  virtual void get_next_request(std::shared_ptr<Request>& req,
                                size_t& client_index) override;
  virtual state_t handle_response(
      const std::shared_ptr<Response>& resp) override;
  virtual void make_response(const std::shared_ptr<Response>& resp) override;

 private:
  int cur_status_ = RESP_OK;
  std::shared_ptr<Response> cur_response_;
  std::shared_ptr<Request> cur_request_;
  std::shared_ptr<BaseConfig> config_;
  std::string exception_description_;
  std::shared_ptr<BaseCommand> command_;
};

#endif  // DETAILSHANDLER_H
