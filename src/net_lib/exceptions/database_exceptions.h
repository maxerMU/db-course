#ifndef DATABASE_EXCEPTIONS_H
#define DATABASE_EXCEPTIONS_H

#include "base_exception.h"

class DatabaseException : public BaseException {
 public:
  DatabaseException() = default;
  DatabaseException(const std::string& message) : BaseException(message) {}

  const char* what() const noexcept override { return "Database error."; }
};

class DatabaseConnectException : public DatabaseException {
 public:
  DatabaseConnectException() = default;
  DatabaseConnectException(const std::string& message)
      : DatabaseException(message) {}

  const char* what() const noexcept override {
    return "Can't connect to database.";
  }
};

#endif  // DATABASE_EXCEPTIONS_H
