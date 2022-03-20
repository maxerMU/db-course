#ifndef READ_AWAITER_H
#define READ_AWAITER_H

#include <coroutine>
#include <string>

#include "net.h"

struct HttpReadAwaiter {
  bool await_ready();

  void await_suspend(std::coroutine_handle<> h);

  http::request<http::string_body> await_resume();

  tcp::socket &sock_;

  beast::flat_buffer buf_;
  http::request<http::string_body> req_;
  error_code ec_;
  size_t bytes_read_;
};

HttpReadAwaiter HttpAsyncRead(tcp::socket &socket);

#endif // READ_AWAITER_H
