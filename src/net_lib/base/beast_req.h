#ifndef BEASTREQ_H
#define BEASTREQ_H

#include "net.h"
#include "reqresp.h"
#include <map>

class BeastReq : public Request {
public:
  BeastReq() = default;
  BeastReq(const http::request<http::string_body> &req);
  virtual std::string get_body() override;
  virtual std::string get_target() override;
  virtual headers_t get_headers() override;
  virtual method_t get_method() override;

  virtual void set_body(const std::string &body) override;
  virtual void set_headers(const headers_t &headers) override;
  virtual void set_target(const std::string &target) override;
  virtual void set_method(const method_t &method) override;

private:
  bool is_from_req = false;
  http::request<http::string_body> req_;
  std::map<std::string, method_t> methods_from{{"GET", GET},
                                               {"POST", POST},
                                               {"DELETE", DELETE},
                                               {"PUT", PUT},
                                               {"PATCH", PATCH}};

  std::string body_;
  headers_t headers_;
  std::string target_;
  method_t method_;
};

http::request<http::string_body>
make_beast_req(const std::shared_ptr<Request> &req);

#endif // BEASTREQ_H
