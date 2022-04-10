#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class BaseException : public std::exception {
public:
  BaseException() = default;
  explicit BaseException(const std::string &message) : error_info(message) {}

  const char *what() const noexcept override {
    return "Something wrong with viewer.";
  }

  const std::string &get_info() const noexcept { return error_info; }

protected:
  std::string error_info;
};

#endif // EXCEPTIONS_H
