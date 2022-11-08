#include "client_server_connection.h"
#include <boost/thread.hpp>
#include <chrono>
#include <iostream>
#include "base_sections.h"

ClientServerConnection::ClientServerConnection(
    net::io_context& context,
    const std::shared_ptr<ClientServerSessionCreator>& creator,
    const std::shared_ptr<BaseConfig>& config)
    : session_creator_(creator),
      acceptor_(context),
      context_(context),
      config_(config) {
  // connet_client_sockets(config);
  connect_server_socket(config);
}

std::vector<std::shared_ptr<tcp::socket>>
ClientServerConnection::connet_client_sockets(
    const std::shared_ptr<BaseConfig>& config) {
  std::vector<std::shared_ptr<tcp::socket>> client_sockets;
  std::vector<std::string> clients = config->get_string_array({ClientsSection});

  for (auto client : clients) {
    std::cout << "Connecting to " << client << "..." << std::endl;
    std::string host = config->get_string_field({client, ClientHostSection});
    int port = config->get_int_field({client, ClientPortSection});
    tcp::endpoint ep(net::ip::address::from_string(host), port);  // TODO

    std::shared_ptr<tcp::socket> client_sock(new tcp::socket(context_));
    client_sock->connect(ep);

    client_sockets.push_back(client_sock);
    std::cout << "Connected" << std::endl;
  }

  return client_sockets;
}

void ClientServerConnection::connect_server_socket(
    const std::shared_ptr<BaseConfig>& config) {
  error_code ec;

  int port = config->get_int_field({ServerSection, PortSection});

  tcp::endpoint ep(net::ip::address_v4(), port);

  acceptor_.open(ep.protocol(), ec);
  if (ec) {
    fail(ec, "open acceptor");
    return;
  }

  acceptor_.set_option(net::socket_base::reuse_address(true), ec);
  if (ec) {
    fail(ec, "set option");
    return;
  }

  acceptor_.bind(ep, ec);
  if (ec) {
    fail(ec, "bind");
    return;
  }

  acceptor_.listen(net::socket_base::max_listen_connections, ec);
  if (ec) {
    fail(ec, "listen");
    return;
  }
}

void ClientServerConnection::clear_expired_connections() {
  using namespace std::chrono_literals;

  for (size_t i = 0; i < coroutine_sessions_.size(); i++) {
    if (coroutine_sessions_[i].second.wait_for(0s) ==
        std::future_status::ready) {
      std::cout << "erase session" << std::endl;
      coroutine_sessions_.erase(coroutine_sessions_.begin() + i);
    }
  }
}

void ClientServerConnection::run() {
  accept_new();
  context_.run();
  // boost::thread_group tg;
  // accept_new();
  // for (size_t i = 0; i < boost::thread::hardware_concurrency(); i++) {
  //   tg.create_thread([&]() { context_.run(); });
  // }
  // // context_.run();
  // tg.join_all();
}

void ClientServerConnection::accept_new() {
  clear_expired_connections();

  acceptor_.async_accept([this](error_code ec, tcp::socket sock) {
    client_sockets = connet_client_sockets(config_);

    if (ec) {
      fail(ec, "accept");
      return;
    }
    std::cout << "start new session" << std::endl;
    auto session = session_creator_->create_session();
    auto fut = session->run(std::move(sock), client_sockets);
    coroutine_sessions_.push_back(
        coroutine_cssession_t(session, std::move(fut)));

    accept_new();
  });
}

void ClientServerConnection::fail(const error_code& ec,
                                  const std::string& desc) {
  std::cerr << "error code: " << ec.message() << " description: " << desc
            << std::endl;
}
