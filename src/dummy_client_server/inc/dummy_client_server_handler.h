#ifndef DUMMYCLIENTSERVERHANDLER_H
#define DUMMYCLIENTSERVERHANDLER_H

#include "base_config.h"
#include "client_server_req_handler.h"
#include "net.h"

class DummyClientServerHandler : public ClientServerReqHandler {
public:
  DummyClientServerHandler(const std::shared_ptr<BaseConfig> &config);
  virtual state_t handle_request(const std::shared_ptr<Request> &req) override;
  virtual void get_next_request(std::shared_ptr<Request> &req,
                                size_t &client_index) override;
  virtual state_t
  handle_response(const std::shared_ptr<Response> &resp) override;
  virtual void make_response(const std::shared_ptr<Response> &resp) override;

private:
  std::shared_ptr<BaseConfig> config_;

  std::string cur_body;

  enum DummyClientServerState {
    NOT_INITIALIZED,
    REQ_HANDLED,
    DUMMY1,
    DUMMY2,
    FINISH
  };

  DummyClientServerState state_ = NOT_INITIALIZED;
};

#endif // DUMMYCLIENTSERVERHANDLER_H
