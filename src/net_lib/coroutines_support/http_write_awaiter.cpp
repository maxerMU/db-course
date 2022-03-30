#include "http_write_awaiter.h"
#include <iostream>

HttpWriteResponseAwaiter
HttpAsyncWriteResponse(tcp::socket &socket,
                       http::response<http::string_body> res) {
  return HttpWriteResponseAwaiter{socket, res};
}

HttpWriteRequestAwaiter
HttpAsyncWriteRequest(tcp::socket &socket,
                      http::request<http::string_body> res) {
  return HttpWriteRequestAwaiter{socket, res};
}

bool HttpWriteResponseAwaiter::await_ready() { return false; }

void HttpWriteResponseAwaiter::await_suspend(std::coroutine_handle<> h) {
  http::async_write(sock_, res_, [this, h](auto ec, auto bytes_read) mutable {
    ec_ = ec;
    bytes_read_ = bytes_read;
    h.resume();
  });
}

size_t HttpWriteResponseAwaiter::await_resume() {
  if (ec_) {
    throw std::system_error(ec_);
  }
  return bytes_read_;
}

bool HttpWriteRequestAwaiter::await_ready() { return false; }

void HttpWriteRequestAwaiter::await_suspend(std::coroutine_handle<> h) {
  http::async_write(sock_, res_, [this, h](auto ec, auto bytes_read) mutable {
    ec_ = ec;
    bytes_read_ = bytes_read;
    h.resume();
  });
}

size_t HttpWriteRequestAwaiter::await_resume() {
  if (ec_) {
    throw std::system_error(ec_);
  }
  return bytes_read_;
}
