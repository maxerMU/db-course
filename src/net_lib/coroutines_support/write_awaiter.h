#ifndef WRITE_AWAITER_H
#define WRITE_AWAITER_H

#include "net.h"
#include <coroutine>

struct WriteAwaiter {
  bool await_ready();

  void await_suspend(std::coroutine_handle<> h);

  void await_resume();

  // Arguments
  tcp::socket &socket_;
  boost::asio::const_buffer buffer_;

  std::error_code ec_;
};

WriteAwaiter AsyncWrite(tcp::socket &socket, boost::asio::const_buffer buffer);

#endif // WRITE_AWAITER_H
