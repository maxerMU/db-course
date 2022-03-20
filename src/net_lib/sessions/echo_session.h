#ifndef ECHO_SESSION_H
#define ECHO_SESSION_H

#include "base_session.h"

class EchoSession : public BaseServerSession,
                    public std::enable_shared_from_this<EchoSession> {
public:
  EchoSession() = default;

  virtual std::future<void> run(tcp::socket sock) override;
};

class EchoSessionCreator : public ServerSessionCreator {
public:
  EchoSessionCreator() = default;
  virtual ~EchoSessionCreator() = default;

  std::shared_ptr<BaseServerSession> create_session() override {
    return std::shared_ptr<BaseServerSession>(new EchoSession());
  }
};

#endif // ECHO_SESSION_H
