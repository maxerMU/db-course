#include "http_read_awaiter.h"
#include <iostream>

HttpReadAwaiter HttpAsyncRead(tcp::socket &socket) {
  return HttpReadAwaiter{socket};
}

bool HttpReadAwaiter::await_ready() { return false; }

void HttpReadAwaiter::await_suspend(std::coroutine_handle<> h) {
  http::async_read(sock_, buf_, req_,
                   [this, h](auto ec, auto bytes_read) mutable {
                     ec_ = ec;
                     bytes_read_ = bytes_read;
                     h.resume();
                   });
}

http::request<http::string_body> HttpReadAwaiter::await_resume() {
  if (ec_) {
    throw std::system_error(ec_);
  }
  return req_;
}
