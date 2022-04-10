#ifndef REQRESP_H
#define REQRESP_H

#include <memory>
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

  virtual void set_body(const std::string& body) = 0;
  virtual void set_headers(const headers_t& headers) = 0;
  virtual void set_target(const std::string& target) = 0;
  virtual void set_method(const method_t& method) = 0;

  void copy(const std::shared_ptr<Request>& another_req) {
    this->set_body(another_req->get_body());
    this->set_target(another_req->get_target());
    this->set_headers(another_req->get_headers());
    this->set_method(another_req->get_method());
  }
};

#define RESP_OK 200
#define RESP_NOT_FOUND 404
#define RESP_INTERNAL_SERVER_ERROR 503

class Response {
 public:
  virtual std::string get_body() const = 0;
  virtual void set_body(const std::string& body) = 0;

  virtual headers_t get_headers() const = 0;
  virtual void set_headers(const headers_t& headers) = 0;

  virtual int get_status() const = 0;
  virtual void set_status(int status) = 0;

  void copy(const std::shared_ptr<Response>& another_resp) {
    this->set_body(another_resp->get_body());
    this->set_headers(another_resp->get_headers());
    this->set_status(another_resp->get_status());
  }
};

#endif  // REQRESP_H
