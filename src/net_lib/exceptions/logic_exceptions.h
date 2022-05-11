#ifndef LOGIC_EXCEPTIONS_H
#define LOGIC_EXCEPTIONS_H

#include "base_exception.h"

class LogicException : public BaseException {
 public:
  LogicException() = default;
  LogicException(const std::string& message) : BaseException(message) {}

  const char* what() const noexcept override { return "Logic error."; }
};

class NotUniqueUsernameException : public LogicException {
 public:
  NotUniqueUsernameException() = default;
  NotUniqueUsernameException(const std::string& message)
      : LogicException(message) {}

  const char* what() const noexcept override { return "Username not unique"; }
};

class InvalidAuthDataException : public LogicException {
 public:
  InvalidAuthDataException() = default;
  InvalidAuthDataException(const std::string& message)
      : LogicException(message) {}

  const char* what() const noexcept override { return "Invalid auth data"; }
};

#endif  // LOGIC_EXCEPTIONS_H
