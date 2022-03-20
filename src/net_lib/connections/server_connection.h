#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <string>

#include "base_session.h"

class ServerConnection : public std::enable_shared_from_this<ServerConnection> {
public:
  ServerConnection(net::io_context &context,
                   const std::shared_ptr<ServerSessionCreator> &creator,
                   const tcp::endpoint &ep);

  void run();

protected:
  void fail(const error_code &ec, const std::string &desc);

private:
  std::shared_ptr<ServerSessionCreator> session_creator_;
  tcp::acceptor acceptor_;
  net::io_context &context_;
};
