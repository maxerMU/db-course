#ifndef SERVERREQHANDLER_H
#define SERVERREQHANDLER_H

#include "reqresp.h"
#include <memory>

class ServerReqHandler {
public:
  ServerReqHandler() = default;
  ~ServerReqHandler() = default;

  virtual void handle_request(const std::shared_ptr<Request> &req) = 0;
  virtual std::shared_ptr<Response> get_response() = 0;
};

#endif // SERVERREQHANDLER_H
