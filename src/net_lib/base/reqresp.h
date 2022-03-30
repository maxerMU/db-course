#ifndef REQRESP_H
#define REQRESP_H

#include <string>
#include <vector>

typedef std::vector<std::pair<std::string, std::string>> headers_t;

enum method_t { GET, POST, DELETE, PUT, PATCH, UNDEFINED };

class Request {
public:
  Request() = default;

  virtual std::string get_body() = 0;
  virtual std::string get_target() = 0;
  virtual headers_t get_headers() = 0;
  virtual method_t get_method() = 0;

  virtual void set_body(const std::string &body) = 0;
  virtual void set_headers(const headers_t &headers) = 0;
  virtual void set_target(const std::string &target) = 0;
  virtual void set_method(const method_t &method) = 0;
};

class Response {
public:
  virtual std::string get_body() const = 0;
  virtual void set_body(const std::string &body) = 0;

  virtual headers_t get_headers() const = 0;
  virtual void set_headers(const headers_t &headers) = 0;

  virtual int get_status() const = 0;
  virtual void set_status(int status) = 0;
};

#endif // REQRESP_H
