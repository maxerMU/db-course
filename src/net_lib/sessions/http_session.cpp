#include "http_session.h"
#include "beast_req.h"
#include "beast_resp.h"
#include "http_read_awaiter.h"
#include "http_write_awaiter.h"
#include "std_future.hpp"

HttpServerSession::HttpServerSession(
    const std::shared_ptr<ServerReqHandler> &handler)
    : handler_(handler) {}

HttpServerSession::~HttpServerSession() {
  std::cout << "destructor" << std::endl;
}

HttpServerSessionCreator::HttpServerSessionCreator(
    const std::shared_ptr<ServerReqHandler> &handler)
    : handler_(handler) {}

std::future<void> HttpServerSession::run(tcp::socket sock) {
  http::request<http::string_body> req = co_await HttpAsyncReadRequest(sock);

  std::shared_ptr<Request> req_ptr(new BeastReq(req));
  handler_->handle_request(req_ptr);

  std::shared_ptr<Response> resp(new BeastResp());
  handler_->make_response(resp);

  auto res = make_beast_resp(resp);
  size_t bytes_read = co_await HttpAsyncWriteResponse(sock, res);
}
