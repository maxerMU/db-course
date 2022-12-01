#ifndef WORKERSADAPTER_H
#define WORKERSADAPTER_H

#include <map>
#include <string>

#include "base_api_gateway_adapter.h"

class WorkersAdapter : public BaseApiGatewayAdapter {
 public:
  virtual void init(const std::shared_ptr<Request>& req,
                    const std::map<std::string, size_t>& client_indexes,
                    const std::shared_ptr<Response>& cur_response) override;
  virtual state_t make_request(std::shared_ptr<Request>& req,
                               size_t& client_index) override;
  virtual state_t handle_response(
      const std::shared_ptr<Response>& cur_gateway_repsonse,
      const std::shared_ptr<Response>& server_response) override;

 private:
  bool is_initialized = false;
  std::shared_ptr<Request> req_;
  std::map<std::string, size_t> client_indexes_;
};

#endif  // WORKERSADAPTER_H
