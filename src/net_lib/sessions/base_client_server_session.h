#ifndef BASECLIENTSERVERSESSION_H
#define BASECLIENTSERVERSESSION_H

#include <iostream>
#include <memory>

#include "net.h"

class BaseClientServerSession {
public:
  virtual std::future<void>
  run(tcp::socket server_sock,
      const std::vector<std::shared_ptr<tcp::socket>> &clients_sock) = 0;

protected:
  void fail(const error_code &ec, const std::string &desc) {
    std::cerr << "error code: " << ec.message() << " description: " << desc
              << std::endl;
  }
};

class ClientServerSessionCreator {
public:
  ClientServerSessionCreator() = default;
  virtual ~ClientServerSessionCreator() = default;

  virtual std::shared_ptr<BaseClientServerSession> create_session() = 0;
};

#endif // BASECLIENTSERVERSESSION_H
