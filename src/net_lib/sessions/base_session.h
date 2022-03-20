#ifndef BASE_SESSION_H
#define BASE_SESSION_H

#include <iostream>
#include <memory>

#include "net.h"

class BaseServerSession {
public:
  BaseServerSession() = default;
  virtual ~BaseServerSession() = default;

  virtual std::future<void> run(tcp::socket sock) = 0;

protected:
  void fail(const error_code &ec, const std::string &desc) {
    std::cerr << "error code: " << ec.message() << " description: " << desc
              << std::endl;
  }
};

class ServerSessionCreator {
public:
  ServerSessionCreator() = default;
  virtual ~ServerSessionCreator() = default;

  virtual std::shared_ptr<BaseServerSession> create_session() = 0;
};

#endif // BASE_SESSION_H
