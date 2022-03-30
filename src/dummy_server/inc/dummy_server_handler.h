#ifndef DUMMYSERVERHANDLER_H
#define DUMMYSERVERHANDLER_H

#include "base_config.h"
#include "net.h"
#include "server_req_handler.h"

class DummyServerHandler : public ServerReqHandler {
public:
  DummyServerHandler(net::io_context &context_,
                     const std::shared_ptr<BaseConfig> &config);

  virtual void handle_request(const std::shared_ptr<Request> &req) override;
  virtual void make_response(const std::shared_ptr<Response> &resp) override;

private:
  net::io_context &ioc;
  std::string req_body;
  std::string append_string;
};

#endif // DUMMYSERVERHANDLER_H
