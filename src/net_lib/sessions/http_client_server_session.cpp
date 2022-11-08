#include "http_client_server_session.h"
#include "beast_req.h"
#include "beast_resp.h"
#include "http_read_awaiter.h"
#include "http_write_awaiter.h"
#include "std_future.hpp"

HttpClientServerSessionCreator::HttpClientServerSessionCreator(
    const std::shared_ptr<BaseClientServerReqHandlerCreator>& creator)
    : creator_(creator) {}

HttpClientServerSession::HttpClientServerSession(
    const std::shared_ptr<BaseClientServerReqHandlerCreator>& creator)
    : handler_creator_(creator) {}

std::future<void> HttpClientServerSession::run(
    tcp::socket server_sock,
    const std::vector<std::shared_ptr<tcp::socket>>& clients_sock) {
  while (true) {
    http::request<http::string_body> req =
        co_await HttpAsyncReadRequest(server_sock);
    std::cout << "read from socket" << std::endl;

    auto handler_ = handler_creator_->create_handler();

    std::shared_ptr<Request> req_ptr(new BeastReq(req));
    auto state = handler_->handle_request(req_ptr);

    while (state == RES_CONTINUE) {
      std::shared_ptr<Request> server_req(new BeastReq());
      size_t next_client;

      handler_->get_next_request(server_req, next_client);

      auto beast_req = make_beast_req(server_req);
      std::cout << "next client: " << next_client << std::endl;
      std::cout << "is connected: " << clients_sock[next_client]->is_open()
                << std::endl;
      std::cout << req_ptr->get_body() << std::endl;
      std::cout << req_ptr->get_target() << std::endl;
      co_await HttpAsyncWriteRequest(*(clients_sock[next_client]), beast_req);
      std::cout << "write to client socket" << std::endl;
      http::response<http::string_body> client_resp =
          co_await HttpAsyncReadResponse(*(clients_sock[next_client]));
      std::cout << "read from client socket" << std::endl;

      std::shared_ptr<Response> client_resp_ptr(new BeastResp(client_resp));
      state = handler_->handle_response(client_resp_ptr);
    }

    std::shared_ptr<Response> resp(new BeastResp());
    handler_->make_response(resp);

    auto res = make_beast_resp(resp);

    size_t bytes_read = co_await HttpAsyncWriteResponse(server_sock, res);
    std::cout << "write to socket" << std::endl;
  }
  for (auto sock : clients_sock) {
    sock->close();
  }
  co_return;
}
