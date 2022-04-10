#ifndef HTTPCLIENTSERVERSESSION_H
#define HTTPCLIENTSERVERSESSION_H

#include "base_client_server_session.h"
#include "client_server_req_handler.h"

class HttpClientServerSession : public BaseClientServerSession {
public:
  HttpClientServerSession(
      const std::shared_ptr<BaseClientServerReqHandlerCreator> &creator);

  virtual std::future<void>
  run(tcp::socket server_sock,
      const std::vector<std::shared_ptr<tcp::socket>> &clients_sock) override;

private:
  std::shared_ptr<BaseClientServerReqHandlerCreator> handler_creator_;
};

class HttpClientServerSessionCreator : public ClientServerSessionCreator {
public:
  HttpClientServerSessionCreator(
      const std::shared_ptr<BaseClientServerReqHandlerCreator> &creator);
  virtual ~HttpClientServerSessionCreator() = default;

  std::shared_ptr<BaseClientServerSession> create_session() override {
    return std::shared_ptr<BaseClientServerSession>(
        new HttpClientServerSession(creator_));
  }

private:
  std::shared_ptr<BaseClientServerReqHandlerCreator> creator_;
};

#endif // HTTPCLIENTSERVERSESSION_H
