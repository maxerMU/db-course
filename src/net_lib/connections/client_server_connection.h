#ifndef CLIENTSERVERCONNECTION_H
#define CLIENTSERVERCONNECTION_H

#include "base_client_server_session.h"
#include "base_config.h"
#include "net.h"

using coroutine_cssession_t =
    std::pair<std::shared_ptr<BaseClientServerSession>, std::future<void>>;

class ClientServerConnection {
 public:
  ClientServerConnection(
      net::io_context& context,
      const std::shared_ptr<ClientServerSessionCreator>& creator,
      const std::shared_ptr<BaseConfig>& config);

  void run();

 protected:
  void fail(const error_code& ec, const std::string& desc);

 private:
  void connect_server_socket(const std::shared_ptr<BaseConfig>& config);
  std::vector<std::shared_ptr<tcp::socket>> connet_client_sockets(
      const std::shared_ptr<BaseConfig>& config);
  void accept_new();
  void clear_expired_connections();

  std::vector<coroutine_cssession_t> coroutine_sessions_;
  std::vector<std::shared_ptr<tcp::socket>> client_sockets;
  std::shared_ptr<ClientServerSessionCreator> session_creator_;
  tcp::acceptor acceptor_;
  net::io_context& context_;
  std::shared_ptr<BaseConfig> config_;
};

#endif  // CLIENTSERVERCONNECTION_H
