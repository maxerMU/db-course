#ifndef READ_AWAITER_H
#define READ_AWAITER_H

#include <coroutine>
#include <string>

#include "net.h"

struct HttpReadRequestAwaiter {
  bool await_ready();

  void await_suspend(std::coroutine_handle<> h);

  http::request<http::string_body> await_resume();

  tcp::socket &sock_;

  beast::flat_buffer buf_;
  http::request<http::string_body> req_;
  error_code ec_;
  size_t bytes_read_;
};

HttpReadRequestAwaiter HttpAsyncReadRequest(tcp::socket &socket);

struct HttpReadResponseAwaiter {
  bool await_ready();

  void await_suspend(std::coroutine_handle<> h);

  http::response<http::string_body> await_resume();

  tcp::socket &sock_;

  beast::flat_buffer buf_;
  http::response<http::string_body> resp_;
  error_code ec_;
  size_t bytes_read_;
};

HttpReadResponseAwaiter HttpAsyncReadResponse(tcp::socket &socket);

#endif // READ_AWAITER_H
