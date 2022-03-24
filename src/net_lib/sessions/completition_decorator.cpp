#include "completition_decorator.h"

CompletitionDecorator::CompletitionDecorator(const std::shared_ptr<BaseServerSession> &session)
    :session_(session)
{
}

std::future<void> CompletitionDecorator::run(tcp::socket sock) {
    session_->run(std::move(sock));
    completed = true;
}
