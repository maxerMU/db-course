#include "http_session.h"
#include "beast_req.h"
#include "http_read_awaiter.h"
#include "http_write_awaiter.h"
#include "std_future.hpp"

HttpServerSession::HttpServerSession(
    const std::shared_ptr<ServerReqHandler> &handler)
    : handler_(handler) {}

HttpServerSessionCreator::HttpServerSessionCreator(
    const std::shared_ptr<ServerReqHandler> &handler)
    : handler_(handler) {}

std::future<void> HttpServerSession::run(tcp::socket sock) {
  http::request<http::string_body> req = co_await HttpAsyncRead(sock);

  std::shared_ptr<Request> req_ptr(new BeastReq(req));
  handler_->handle_request(req_ptr);

  auto resp = handler_->get_response();

  http::response<http::string_body> res(http::status(resp->get_status()), 11);
  res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
  res.set(http::field::content_type, "text/html");
  res.keep_alive(req_.keep_alive());
  res.body() = std::string{resp->get_body()};
  res.prepare_payload();

  std::cout << "ready" << std::endl;

  size_t bytes_read = co_await HttpAsyncWrite(sock, res);
}
