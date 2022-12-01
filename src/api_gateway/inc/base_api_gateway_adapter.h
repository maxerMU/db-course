#ifndef BASE_API_GATEWAY_ADAPTER_H
#define BASE_API_GATEWAY_ADAPTER_H

#include <functional>

#include "client_server_req_handler.h"

class BaseApiGatewayAdapter {
 public:
  virtual void init(const std::shared_ptr<Request>& req,
                    const std::map<std::string, size_t>& client_indexes,
                    const std::shared_ptr<Response>& cur_gateway_resp) = 0;
  virtual state_t make_request(std::shared_ptr<Request>& req,
                               size_t& client_index) = 0;
  virtual state_t handle_response(
      const std::shared_ptr<Response>& cur_gateway_repsonse,
      const std::shared_ptr<Response>& server_response) = 0;
};

class BaseApiGatewayAdapterCreator {
 public:
  BaseApiGatewayAdapterCreator() = default;
  ~BaseApiGatewayAdapterCreator() = default;

  virtual std::shared_ptr<BaseApiGatewayAdapter> create_adapter() const = 0;
};

template <class T>
concept base_api_gateway_adapter =
    std::is_base_of<BaseApiGatewayAdapter, T>::value;

template <base_api_gateway_adapter T>
class ApiGatewayAdapterCreator : public BaseApiGatewayAdapterCreator {
 public:
  template <typename... Args>
  ApiGatewayAdapterCreator(Args... args) {
    create_func_ = [args...]() {
      return std::shared_ptr<BaseApiGatewayAdapter>(new T(args...));
    };
  }

  std::shared_ptr<BaseApiGatewayAdapter> create_adapter() const override {
    return create_func_();
  }

 private:
  std::function<std::shared_ptr<BaseApiGatewayAdapter>()> create_func_;
};

#endif  // BASE_API_GATEWAY_ADAPTER_H
