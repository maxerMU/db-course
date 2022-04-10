#ifndef BASECOMMAND_H
#define BASECOMMAND_H

#include <functional>
#include <regex>
#include "details_facade.h"
#include "reqresp.h"

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

class DetailsForAllTimeCommand : public BaseCommand {
 public:
  virtual void handle_request(const std::shared_ptr<Request>& req) override;
  virtual void get_response(const std::shared_ptr<Response>& resp) override;

 private:
  details_t details;
};

class DetailsInStockCommand : public BaseCommand {
 public:
  virtual void handle_request(const std::shared_ptr<Request>& req) override;
  virtual void get_response(const std::shared_ptr<Response>& resp) override;

 private:
  details_t details;
};

class DetailSwapsCommand : public BaseCommand {
 public:
  DetailSwapsCommand(const std::regex& expr, size_t part_number_group_index)
      : regexpr_(expr), part_number_group_index_(part_number_group_index) {}
  virtual void handle_request(const std::shared_ptr<Request>& req) override;
  virtual void get_response(const std::shared_ptr<Response>& resp) override;

 private:
  std::regex regexpr_;
  size_t part_number_group_index_;
  std::string part_number_;

  details_t details;
};

class AddDetailCommand : public BaseCommand {
 public:
  virtual void handle_request(const std::shared_ptr<Request>& req) override;
  virtual void get_response(const std::shared_ptr<Response>& resp) override;
};

#endif  // BASECOMMAND_H
