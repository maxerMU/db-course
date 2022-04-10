#ifndef DETAILSADAPTER_H
#define DETAILSADAPTER_H

#include <map>
#include <string>
#include "base_api_gateway_adapter.h"

class DetailsAdapter : public BaseApiGatewayAdapter {
 public:
  DetailsAdapter() = default;

 public:
  virtual void init(
      const std::shared_ptr<Request>& req,
      const std::map<std::string, size_t>& client_indexes) override;
  virtual void make_request(std::shared_ptr<Request>& req,
                            size_t& client_index) override;
  virtual state_t handle_response(
      const std::shared_ptr<Response>& cur_gateway_repsonse,
      const std::shared_ptr<Response>& server_response) override;

 private:
  bool is_initialized = false;
  std::shared_ptr<Request> req_;
  std::map<std::string, size_t> client_indexes_;
};

#endif  // DETAILSADAPTER_H
