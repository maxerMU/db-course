#ifndef WRITE_AWAITER_H
#define WRITE_AWAITER_H

#include <coroutine>
#include <string>

#include "net.h"

struct HttpWriteResponseAwaiter {
  bool await_ready();

  void await_suspend(std::coroutine_handle<> h);

  size_t await_resume();

  tcp::socket &sock_;
  http::response<http::string_body> res_;

  error_code ec_;
  size_t bytes_read_;
};

HttpWriteResponseAwaiter
HttpAsyncWriteResponse(tcp::socket &socket,
                       http::response<http::string_body> res);

struct HttpWriteRequestAwaiter {
  bool await_ready();

  void await_suspend(std::coroutine_handle<> h);

  size_t await_resume();

  tcp::socket &sock_;
  http::request<http::string_body> res_;

  error_code ec_;
  size_t bytes_read_;
};

HttpWriteRequestAwaiter
HttpAsyncWriteRequest(tcp::socket &socket,
                      http::request<http::string_body> res);

#endif // WRITE_AWAITER_H
