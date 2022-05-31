#ifndef REQRESP_H
#define REQRESP_H

#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <memory>
#include <string>
#include <vector>
#include "server_exceptions.h"

typedef std::vector<std::pair<std::string, std::string>> headers_t;

enum method_t { GET, POST, DELETE, PUT, PATCH, UNDEFINED };

struct ExtraData {
  ExtraData() = default;
  ExtraData(const std::string& json_str) {
    Json::Value value;
    Json::Reader reader;

    bool parse_successfull = reader.parse(json_str, value);

    if (!parse_successfull) {
      throw JsonParserException("can't parse extra data");
    }

    auth_inf.worker_id = value["worker_id"].asUInt64();
  }
  struct AuthInf {
    size_t worker_id;
  } auth_inf;
};

class Request {
 public:
  Request() = default;

  virtual std::string get_body() = 0;
  virtual std::string get_target() = 0;
  virtual headers_t get_headers() = 0;
  virtual method_t get_method() = 0;
  virtual ExtraData get_extra_data() = 0;

  virtual void set_body(const std::string& body) = 0;
  virtual void set_headers(const headers_t& headers) = 0;
  virtual void set_target(const std::string& target) = 0;
  virtual void set_method(const method_t& method) = 0;
  virtual void set_extra_data(const ExtraData& extra_data) = 0;

  void copy(const std::shared_ptr<Request>& another_req) {
    this->set_body(another_req->get_body());
    this->set_target(another_req->get_target());
    this->set_headers(another_req->get_headers());
    this->set_method(another_req->get_method());
    this->set_extra_data(another_req->get_extra_data());
  }
};

#define RESP_OK 200
#define RESP_UNAUTHIRIZED 401
#define RESP_FORBIDDEN 403
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
