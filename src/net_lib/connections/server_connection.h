#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <vector>

#include "base_session.h"

using coroutine_session_t =
    std::pair<std::shared_ptr<BaseServerSession>, std::future<void>>;

class ServerConnection : public std::enable_shared_from_this<ServerConnection> {
public:
  ServerConnection(net::io_context &context,
                   const std::shared_ptr<ServerSessionCreator> &creator,
                   const tcp::endpoint &ep);

  void run();

protected:
  void fail(const error_code &ec, const std::string &desc);

private:
  void clear_expired_connections();
  std::vector<coroutine_session_t> coroutine_sessions_;
  std::shared_ptr<ServerSessionCreator> session_creator_;
  tcp::acceptor acceptor_;
  net::io_context &context_;
};
