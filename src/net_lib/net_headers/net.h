#ifndef NET_H
#define NET_H

#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace net = boost::asio;
namespace beast = boost::beast;
namespace http = boost::beast::http;

using tcp = net::ip::tcp;
using error_code = boost::system::error_code;

#endif // NET_H
