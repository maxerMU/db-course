#ifndef APIGATEWAYHANDLER_H
#define APIGATEWAYHANDLER_H

#include "net.h"
#include "server_req_handler.h"

class ApiGatewayHandler : public ServerReqHandler {
public:
  ApiGatewayHandler(net::io_context &context_);

  virtual void handle_request(const std::shared_ptr<Request> &req) override;
  virtual void make_response(const std::shared_ptr<Response> &resp) override;

private:
  net::io_context &ioc;
};

#endif // APIGATEWAYHANDLER_H
