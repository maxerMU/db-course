#ifndef CLIENTSERVERREQHANDLER_H
#define CLIENTSERVERREQHANDLER_H

#include "memory"
#include "reqresp.h"

enum state_t { RES_CONTINUE, RES_END };

class ClientServerReqHandler {
public:
  virtual state_t handle_request(const std::shared_ptr<Request> &req) = 0;
  virtual void get_next_request(std::shared_ptr<Request> &req,
                                size_t &client_index) = 0;
  virtual state_t handle_response(const std::shared_ptr<Response> &resp) = 0;
  virtual void make_response(const std::shared_ptr<Response> &resp) = 0;
};

#endif // CLIENTSERVERREQHANDLER_H
