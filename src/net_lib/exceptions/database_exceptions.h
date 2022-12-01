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

class DatabaseExecutionException : public DatabaseException {
 public:
  DatabaseExecutionException() = default;
  DatabaseExecutionException(const std::string& message)
      : DatabaseException(message) {}

  const char* what() const noexcept override {
    return "Can't execute prepared statement.";
  }
};

class DatabaseNotFoundException : public DatabaseException {
 public:
  DatabaseNotFoundException() = default;
  DatabaseNotFoundException(const std::string& message)
      : DatabaseException(message) {}

  const char* what() const noexcept override {
    return "Can't find in database";
  }
};

class DatabaseIncorrectAnswerException : public DatabaseException {
 public:
  DatabaseIncorrectAnswerException() = default;
  DatabaseIncorrectAnswerException(const std::string& message)
      : DatabaseException(message) {}

  const char* what() const noexcept override {
    return "Incorrect answer from database";
  }
};

class DatabaseNotUniqueUsernameException : public DatabaseException {
 public:
  DatabaseNotUniqueUsernameException() = default;
  DatabaseNotUniqueUsernameException(const std::string& message)
      : DatabaseException(message) {}

  const char* what() const noexcept override { return "Not Unique Username"; }
};

#endif  // DATABASE_EXCEPTIONS_H
