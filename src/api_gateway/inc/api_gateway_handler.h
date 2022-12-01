#ifndef APIGATEWAYHANDLER_H
#define APIGATEWAYHANDLER_H

#include "api_gateway_router.h"
#include "client_server_req_handler.h"
#include "net.h"
#include "yamlcpp_config.h"

class ApiGatewayHandler : public ClientServerReqHandler {
 public:
  ApiGatewayHandler(const std::shared_ptr<BaseConfig> &config);
  virtual state_t handle_request(const std::shared_ptr<Request> &req) override;
  virtual state_t get_next_request(std::shared_ptr<Request> &req,
                                   size_t &client_index) override;
  virtual state_t handle_response(
      const std::shared_ptr<Response> &resp) override;
  virtual void make_response(const std::shared_ptr<Response> &resp) override;

 private:
  int cur_status = RESP_OK;
  std::shared_ptr<Response> cur_response_;
  std::shared_ptr<Request> cur_request_;
  std::shared_ptr<BaseConfig> config_;
  adapters_t cur_adapters_;
  size_t cur_adapter_index_;
};

#endif  // APIGATEWAYHANDLER_H
