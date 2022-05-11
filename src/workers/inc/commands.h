#ifndef BASECOMMAND_H
#define BASECOMMAND_H

#include <functional>
#include <regex>
#include "reqresp.h"
#include "workers_facade.h"

class BaseCommand {
 public:
  virtual void handle_request(const std::shared_ptr<Request>& req) = 0;
  virtual void get_response(const std::shared_ptr<Response>& resp) = 0;
};

class BaseCommandCreator {
 public:
  BaseCommandCreator() = default;
  ~BaseCommandCreator() = default;

  virtual std::shared_ptr<BaseCommand> create_command() const = 0;
};

template <class T>
concept base_command = std::is_base_of<BaseCommand, T>::value;

template <base_command T>
class CommandCreator : public BaseCommandCreator {
 public:
  template <typename... Args>
  CommandCreator(Args... args) {
    create_func_ = [args...]() {
      return std::shared_ptr<BaseCommand>(new T(args...));
    };
  }

  ~CommandCreator() = default;

  std::shared_ptr<BaseCommand> create_command() const override {
    return create_func_();
  }

 private:
  std::function<std::shared_ptr<BaseCommand>()> create_func_;
};

class AddWorkerCommand : public BaseCommand {
 public:
  virtual void handle_request(const std::shared_ptr<Request>& req) override;
  virtual void get_response(const std::shared_ptr<Response>& resp) override;
};

class LoginCommand : public BaseCommand {
 public:
  virtual void handle_request(const std::shared_ptr<Request>& req) override;
  virtual void get_response(const std::shared_ptr<Response>& resp) override;

 private:
  std::string token_;
  int status_code_ = RESP_OK;
};

#endif  // BASECOMMAND_H
