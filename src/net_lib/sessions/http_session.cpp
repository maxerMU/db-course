#include "http_session.h"
#include "beast_req.h"
#include "beast_resp.h"
#include "http_read_awaiter.h"
#include "http_write_awaiter.h"
#include "std_future.hpp"

HttpServerSession::HttpServerSession(
    const std::shared_ptr<BaseServerReqHandlerCreator>& creator)
    : handler_creator_(creator) {}

HttpServerSession::~HttpServerSession() {
  std::cout << "destructor" << std::endl;
}

HttpServerSessionCreator::HttpServerSessionCreator(
    const std::shared_ptr<BaseServerReqHandlerCreator>& creator)
    : handler_creator_(creator) {}

std::future<void> HttpServerSession::run(tcp::socket sock) {
  while (true) {
    auto handler_ = handler_creator_->create_handler();
    std::pair<http::request<http::string_body>, size_t> read_res =
        co_await HttpAsyncReadRequest(sock);
    if (read_res.second == 0) {
      break;
    }
    http::request<http::string_body> req = read_res.first;

    std::shared_ptr<Request> req_ptr(new BeastReq(req));
    handler_->handle_request(req_ptr);

    std::shared_ptr<Response> resp(new BeastResp());
    handler_->make_response(resp);

    auto res = make_beast_resp(resp);
    size_t bytes_read = co_await HttpAsyncWriteResponse(sock, res);
  }

  sock.close();
}
