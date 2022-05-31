#ifndef BASECOMMAND_H
#define BASECOMMAND_H

#include <functional>
#include <regex>
#include "privilege_level.h"
#include "reqresp.h"
#include "workers_facade.h"

class BaseCommand {
 public:
  virtual void handle_request(const std::shared_ptr<Request>& req) = 0;
  virtual void get_response(const std::shared_ptr<Response>& resp) = 0;
  virtual PrivilegeLevel get_min_privilege_level() = 0;
  virtual bool need_auth() = 0;
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

class BaseAuthCommand : public BaseCommand {
 public:
  virtual bool need_auth() { return true; }
};

class BaseNoAuthCommand : public BaseCommand {
 public:
  virtual bool need_auth() { return false; }
};

class AddWorkerCommand : public BaseNoAuthCommand {
 public:
  virtual void handle_request(const std::shared_ptr<Request>& req) override;
  virtual void get_response(const std::shared_ptr<Response>& resp) override;
  virtual PrivilegeLevel get_min_privilege_level() override;
};

class LoginCommand : public BaseNoAuthCommand {
 public:
  virtual void handle_request(const std::shared_ptr<Request>& req) override;
  virtual void get_response(const std::shared_ptr<Response>& resp) override;
  virtual PrivilegeLevel get_min_privilege_level() override;

 private:
  std::string token_;
  int status_code_ = RESP_OK;
};

class AuthCommand : public BaseNoAuthCommand {
 public:
  virtual void handle_request(const std::shared_ptr<Request>& req) override;
  virtual void get_response(const std::shared_ptr<Response>& resp) override;
  virtual PrivilegeLevel get_min_privilege_level() override;

 private:
  std::string token_;
  size_t worker_id_;
  int status_code_ = RESP_OK;
};

class GetWorkerCommand : public BaseAuthCommand {
 public:
  virtual void handle_request(const std::shared_ptr<Request>& req) override;
  virtual void get_response(const std::shared_ptr<Response>& resp) override;
  virtual PrivilegeLevel get_min_privilege_level() override;

 private:
  WorkerGet worker_;
  int status_code_ = RESP_OK;
};

class UpdateWorkerCommand : public BaseAuthCommand {
 public:
  virtual void handle_request(const std::shared_ptr<Request>& req) override;
  virtual void get_response(const std::shared_ptr<Response>& resp) override;
  virtual PrivilegeLevel get_min_privilege_level() override;

 private:
  int status_code_ = RESP_OK;
};

class UpdatePrivilegeCommand : public BaseAuthCommand {
 public:
  UpdatePrivilegeCommand(const std::regex& expr, size_t worker_id_group_index)
      : regexpr_(expr), worker_id_group_index_(worker_id_group_index) {}
  virtual void handle_request(const std::shared_ptr<Request>& req) override;
  virtual void get_response(const std::shared_ptr<Response>& resp) override;
  virtual PrivilegeLevel get_min_privilege_level() override;

 private:
  std::regex regexpr_;
  size_t worker_id_group_index_;
  std::string part_number_;
};

#endif  // BASECOMMAND_H
