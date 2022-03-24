#ifndef COMPLETITIONDECORATOR_H
#define COMPLETITIONDECORATOR_H

#include <base_session.h>

class CompletitionDecorator : public BaseServerSession
{
public:
    CompletitionDecorator(const std::shared_ptr<BaseServerSession> &session);
  virtual std::future<void> run(tcp::socket sock) override;

private:
    std::shared_ptr<BaseServerSession> session_;
};

#endif // COMPLETITIONDECORATOR_H
