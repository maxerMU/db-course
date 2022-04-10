#ifndef SERVER_EXCEPTIONS_H
#define SERVER_EXCEPTIONS_H

#include "base_exception.h"

class ServerException : public BaseException {
 public:
  ServerException() = default;
  ServerException(const std::string& message) : BaseException(message) {}

  const char* what() const noexcept override { return "Server error."; }
};

class JsonParserException : public ServerException {
 public:
  JsonParserException() = default;
  JsonParserException(const std::string& message) : ServerException(message) {}

  const char* what() const noexcept override { return "Json parser error."; }
};

class RegExpParserException : public ServerException {
 public:
  RegExpParserException() = default;
  RegExpParserException(const std::string& message)
      : ServerException(message) {}

  const char* what() const noexcept override {
    return "Regular expression parser error.";
  }
};

#endif  // SERVER_EXCEPTIONS_H
