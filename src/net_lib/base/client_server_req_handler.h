#ifndef CLIENTSERVERREQHANDLER_H
#define CLIENTSERVERREQHANDLER_H

#include "base_config.h"
#include "base_sections.h"
#include "reqresp.h"
#include <functional>
#include <map>
#include <memory>

enum state_t { RES_CONTINUE, RES_END };

class ClientServerReqHandler {
public:
  virtual state_t handle_request(const std::shared_ptr<Request> &req) = 0;
  virtual void get_next_request(std::shared_ptr<Request> &req,
                                size_t &client_index) = 0;
  virtual state_t handle_response(const std::shared_ptr<Response> &resp) = 0;
  virtual void make_response(const std::shared_ptr<Response> &resp) = 0;

protected:
  std::map<std::string, size_t> client_indexes;
  void set_client_indexes(const std::shared_ptr<BaseConfig> &config) {
    client_indexes.clear();
    std::vector<std::string> clients =
        config->get_string_array({ClientsSection});

    for (size_t i = 0; i < clients.size(); i++)
      client_indexes[clients[i]] = i;
  }
};

class BaseClientServerReqHandlerCreator {
public:
  BaseClientServerReqHandlerCreator() = default;
  ~BaseClientServerReqHandlerCreator() = default;

  virtual std::shared_ptr<ClientServerReqHandler> create_handler() const = 0;
};

template <class T>
concept base_client_server_handler =
    std::is_base_of<ClientServerReqHandler, T>::value;

template <base_client_server_handler T>
class ClientServerReqHandlerCreator : public BaseClientServerReqHandlerCreator {
public:
  template <typename... Args> ClientServerReqHandlerCreator(Args... args) {
    create_func_ = [args...]() {
      return std::shared_ptr<ClientServerReqHandler>(new T(args...));
    };
  }

  ~ClientServerReqHandlerCreator() = default;

  std::shared_ptr<ClientServerReqHandler> create_handler() const override {
    return create_func_();
  }

private:
  std::function<std::shared_ptr<ClientServerReqHandler>()> create_func_;
};

#endif // CLIENTSERVERREQHANDLER_H
