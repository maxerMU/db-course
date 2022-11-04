#include "server_connection.h"

#include <boost/thread.hpp>
#include <chrono>
#include <iostream>
#include "base_sections.h"
#include "completition_decorator.h"
#include "echo_session.h"
#include "std_future.hpp"

ServerConnection::ServerConnection(
    net::io_context& context,
    const std::shared_ptr<ServerSessionCreator>& creator,
    const std::shared_ptr<BaseConfig>& config)
    : session_creator_(creator), acceptor_(context), context_(context) {
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

void ServerConnection::clear_expired_connections() {
  using namespace std::chrono_literals;

  for (size_t i = 0; i < coroutine_sessions_.size(); i++) {
    if (coroutine_sessions_[i].second.wait_for(0s) ==
        std::future_status::ready) {
      coroutine_sessions_.erase(coroutine_sessions_.begin() + i);
    }
  }
}

void ServerConnection::run() {
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

void ServerConnection::accept_new() {
  clear_expired_connections();

  acceptor_.async_accept([this](error_code ec, tcp::socket sock) {
    accept_new();
    if (ec) {
      fail(ec, "accept");
      return;
    }
    std::cout << "start new session" << std::endl;
    auto session = session_creator_->create_session();
    auto fut = session->run(std::move(sock));
    coroutine_sessions_.push_back(coroutine_session_t(session, std::move(fut)));
  });
}

void ServerConnection::fail(const error_code& ec, const std::string& desc) {
  std::cerr << "error code: " << ec.message() << " description: " << desc
            << std::endl;
}
