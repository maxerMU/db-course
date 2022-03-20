#ifndef BEASTREQ_H
#define BEASTREQ_H

#include "net.h"
#include "reqresp.h"
#include <map>

class BeastReq : public Request {
public:
  BeastReq(const http::request<http::string_body> &req);
  virtual std::string get_body() override;
  virtual std::string get_target() override;
  virtual headers_t get_headers() override;
  virtual method_t get_method() override;

private:
  http::request<http::string_body> req_;
  std::map<std::string, method_t> methods{
      {"GET", GET}, {"POST", POST}, {"DELETE", DELETE}, {"CREATE", CREATE},
      {"PUT", PUT}, {"EDIT", EDIT}, {"PATCH", PATCH}};
};

#endif // BEASTREQ_H
