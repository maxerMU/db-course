#include "echo_session.h"
#include <boost/bind.hpp>
#include <memory>
#include <time.h>

#include "read_awaiter.h"
#include "std_future.hpp"
#include "write_awaiter.h"

#define BUF_LEN 1024

std::future<void> EchoSession::run(tcp::socket sock) {
  char buf[BUF_LEN];

  while (true) {
    size_t bytes_read = co_await AsyncRead(sock, boost::asio::buffer(buf));
    std::cout << "Server get message: " << buf << std::endl;
    co_await AsyncWrite(sock, {buf, bytes_read});
    std::cout << "Server has sent message" << std::endl;
  }
}
