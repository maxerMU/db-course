#ifndef REQRESP_H
#define REQRESP_H

#include <string>
#include <vector>

typedef std::vector<std::pair<std::string, std::string>> headers_t;

enum method_t { GET, POST, DELETE, CREATE, PUT, EDIT, PATCH, UNDEFINED };

class Request {
public:
  Request() = default;

  virtual std::string get_body() = 0;
  virtual std::string get_target() = 0;
  virtual headers_t get_headers() = 0;
  virtual method_t get_method() = 0;
};

class Response {
public:
  std::string get_body() const;
  void set_body(const std::string &body);

  headers_t get_headers() const;
  void set_headers(const headers_t &headers);

  int get_status() const;
  void set_status(int status);

private:
  std::string body_;
  headers_t headers_;
  int status_ = 200;
};

#endif // REQRESP_H
