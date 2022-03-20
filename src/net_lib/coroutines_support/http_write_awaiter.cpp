#include "http_write_awaiter.h"
#include <iostream>

HttpWriteAwaiter HttpAsyncWrite(tcp::socket &socket,
                                http::response<http::string_body> res) {
  return HttpWriteAwaiter{socket, res};
}

bool HttpWriteAwaiter::await_ready() { return false; }

void HttpWriteAwaiter::await_suspend(std::coroutine_handle<> h) {
  http::async_write(sock_, res_, [this, h](auto ec, auto bytes_read) mutable {
    ec_ = ec;
    bytes_read_ = bytes_read;
    h.resume();
  });
}

size_t HttpWriteAwaiter::await_resume() {
  if (ec_) {
    throw std::system_error(ec_);
  }
  return bytes_read_;
}
