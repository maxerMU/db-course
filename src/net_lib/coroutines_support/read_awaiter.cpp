#include "read_awaiter.h"

ReadAwaiter AsyncRead(tcp::socket &socket, net::mutable_buffer buffer) {
  return ReadAwaiter{socket, buffer};
}

bool ReadAwaiter::await_ready() { return false; }

void ReadAwaiter::await_suspend(std::coroutine_handle<> h) {
  sock_.async_read_some(res_, [this, h](auto &ec, auto bytes_read) mutable {
    ec_ = ec;
    bytes_read_ = bytes_read;
    h.resume();
  });
}

size_t ReadAwaiter::await_resume() {
  if (ec_) {
    throw std::system_error(ec_);
  }
  return bytes_read_;
}
