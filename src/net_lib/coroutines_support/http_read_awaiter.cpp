#include "http_read_awaiter.h"
#include <iostream>

HttpReadRequestAwaiter HttpAsyncReadRequest(tcp::socket& socket) {
  return HttpReadRequestAwaiter{socket};
}

HttpReadResponseAwaiter HttpAsyncReadResponse(tcp::socket& socket) {
  return HttpReadResponseAwaiter{socket};
}

bool HttpReadRequestAwaiter::await_ready() {
  return false;
}

void HttpReadRequestAwaiter::await_suspend(std::coroutine_handle<> h) {
  http::async_read(sock_, buf_, req_,
                   [this, h](auto ec, auto bytes_read) mutable {
                     ec_ = ec;
                     bytes_read_ = bytes_read;
                     h.resume();
                   });
}

std::pair<http::request<http::string_body>, size_t>
HttpReadRequestAwaiter::await_resume() {
  if (ec_) {
    throw std::system_error(ec_);
  }
  return std::pair<http::request<http::string_body>, size_t>(req_, bytes_read_);
}

bool HttpReadResponseAwaiter::await_ready() {
  return false;
}

void HttpReadResponseAwaiter::await_suspend(std::coroutine_handle<> h) {
  http::async_read(sock_, buf_, resp_,
                   [this, h](auto ec, auto bytes_read) mutable {
                     ec_ = ec;
                     bytes_read_ = bytes_read;
                     h.resume();
                   });
}

http::response<http::string_body> HttpReadResponseAwaiter::await_resume() {
  if (ec_) {
    throw std::system_error(ec_);
  }
  return resp_;
}
