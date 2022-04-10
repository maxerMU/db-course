#ifndef HTTP_SESSION_H
#define HTTP_SESSION_H

#include "base_session.h"
#include "server_req_handler.h"

class HttpServerSession : public BaseServerSession {
public:
  HttpServerSession(
      const std::shared_ptr<BaseServerReqHandlerCreator> &creator);
  ~HttpServerSession();

  virtual std::future<void> run(tcp::socket sock) override;

private:
  http::request<http::string_body> req_;
  std::shared_ptr<BaseServerReqHandlerCreator> handler_creator_;
};

class HttpServerSessionCreator : public ServerSessionCreator {
public:
  HttpServerSessionCreator(
      const std::shared_ptr<BaseServerReqHandlerCreator> &creator);
  virtual ~HttpServerSessionCreator() = default;

  std::shared_ptr<BaseServerSession> create_session() override {
    return std::shared_ptr<BaseServerSession>(
        new HttpServerSession(handler_creator_));
  }

private:
  std::shared_ptr<BaseServerReqHandlerCreator> handler_creator_;
};

#endif // HTTP_SESSION_H
