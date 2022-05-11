#ifndef WORKERSHANDLER_H
#define WORKERSHANDLER_H

#include "base_config.h"
#include "commands.h"
#include "net.h"
#include "server_req_handler.h"

class WorkersHandler : public ServerReqHandler {
 public:
  WorkersHandler(const std::shared_ptr<BaseConfig>& config);

  virtual void handle_request(const std::shared_ptr<Request>& req) override;
  virtual void make_response(const std::shared_ptr<Response>& resp) override;

 private:
  int cur_status_;
  std::string exception_description_;
  std::shared_ptr<BaseCommand> command_;
};

#endif  // WORKERSHANDLER_H
