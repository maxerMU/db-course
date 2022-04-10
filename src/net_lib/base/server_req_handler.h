#ifndef SERVERREQHANDLER_H
#define SERVERREQHANDLER_H

#include "reqresp.h"
#include <functional>
#include <memory>

class ServerReqHandler {
public:
  ServerReqHandler() = default;
  ~ServerReqHandler() = default;

  virtual void handle_request(const std::shared_ptr<Request> &req) = 0;
  virtual void make_response(const std::shared_ptr<Response> &resp) = 0;
};

class BaseServerReqHandlerCreator {
public:
  BaseServerReqHandlerCreator() = default;
  ~BaseServerReqHandlerCreator() = default;

  virtual std::shared_ptr<ServerReqHandler> create_handler() const = 0;
};

template <class T>
concept base_server_handler = std::is_base_of<ServerReqHandler, T>::value;

template <base_server_handler T>
class ServerReqHandlerCreator : public BaseServerReqHandlerCreator {
public:
  template <typename... Args> ServerReqHandlerCreator(Args... args) {
    create_func_ = [args...]() {
      return std::shared_ptr<ServerReqHandler>(new T(args...));
    };
  }

  ~ServerReqHandlerCreator() = default;

  std::shared_ptr<ServerReqHandler> create_handler() const override {
    return create_func_();
  }

private:
  std::function<std::shared_ptr<ServerReqHandler>()> create_func_;
};

#endif // SERVERREQHANDLER_H
