#ifndef HTTPCLIENTSERVERSESSION_H
#define HTTPCLIENTSERVERSESSION_H

#include "base_client_server_session.h"
#include "client_server_req_handler.h"

class HttpClientServerSession : public BaseClientServerSession
{
public:
    HttpClientServerSession(const std::shared_ptr<ClientServerReqHandler> &handler);

  virtual std::future<void>
  run(tcp::socket server_sock,
      const std::vector<std::shared_ptr<tcp::socket>> &clients_sock) override;

private:
    std::shared_ptr<ClientServerReqHandler> handler_;
};

#endif // HTTPCLIENTSERVERSESSION_H
