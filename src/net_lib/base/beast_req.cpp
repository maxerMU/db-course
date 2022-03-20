#include "beast_req.h"

BeastReq::BeastReq(const http::request<http::string_body> &req) : req_(req) {}

std::string BeastReq::get_body() { return req_.body(); }

std::string BeastReq::get_target() {
  std::string res(req_.target());
  return res;
}

headers_t BeastReq::get_headers() {
  headers_t res;

  for (auto const &field : req_)
    res.push_back(std::pair<std::string, std::string>(field.name_string(),
                                                      field.value()));

  return res;
}

method_t BeastReq::get_method() {
  std::string method(req_.method_string());

  if (methods.contains(method))
    return methods[method];

  return UNDEFINED;
}
