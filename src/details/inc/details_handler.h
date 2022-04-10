#ifndef DETAILSHANDLER_H
#define DETAILSHANDLER_H

#include "base_config.h"
#include "commands.h"
#include "net.h"
#include "server_req_handler.h"

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

#endif  // DETAILSHANDLER_H
