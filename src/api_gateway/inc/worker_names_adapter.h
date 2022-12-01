#ifndef WORKERNAMESADAPTER_H
#define WORKERNAMESADAPTER_H

#include <regex>
#include <set>

#include "base_api_gateway_adapter.h"

class WorkerNamesAdapter : public BaseApiGatewayAdapter {
 public:
  WorkerNamesAdapter();

  virtual void init(const std::shared_ptr<Request> &req,
                    const std::map<std::string, size_t> &client_indexes,
                    const std::shared_ptr<Response> &cur_gateway_resp) override;
  virtual state_t make_request(std::shared_ptr<Request> &req,
                               size_t &client_index) override;
  virtual state_t handle_response(
      const std::shared_ptr<Response> &cur_gateway_repsonse,
      const std::shared_ptr<Response> &server_response) override;

 private:
  bool is_initialised = false;

  std::regex worker_id_regexp = std::regex("\"worker_id\":(\\d+)");
  std::set<size_t> worker_ids;
  size_t cur_worker_id;

  std::shared_ptr<Request> req_;
  std::map<std::string, size_t> client_indexes_;

  const std::string workers_url = std::string("/workers");
};

#endif  // WORKERNAMESADAPTER_H
