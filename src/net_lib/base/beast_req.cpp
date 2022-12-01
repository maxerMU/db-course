#include "beast_req.h"

#define REQ_VERSION 11

http::request<http::string_body> make_beast_req(
    const std::shared_ptr<Request>& req) {
  // TODO
  std::map<method_t, http::verb> methods_to{{GET, http::verb::get},
                                            {POST, http::verb::post},
                                            {DELETE, http::verb::delete_},
                                            {PUT, http::verb::put},
                                            {PATCH, http::verb::patch}};
  http::verb verb = http::verb::unknown;
  if (methods_to.contains(req->get_method())) {
    verb = methods_to[req->get_method()];
  }

  http::request<http::string_body> res(verb, req->get_target(), REQ_VERSION);

  for (auto header : req->get_headers()) {
    res.set(header.first, header.second);
  }

  res.body() = req->get_body();

  res.prepare_payload();

  return res;
}

BeastReq::BeastReq(const http::request<http::string_body>& req)
    : req_(req), is_from_req(true) {}

std::string BeastReq::get_body() {
  if (is_from_req) return req_.body();

  return body_;
}

std::string BeastReq::get_target() {
  if (!is_from_req) return target_;
  std::string res(req_.target());
  return res;
}

headers_t BeastReq::get_headers() {
  if (!is_from_req) return headers_;

  headers_t res;

  for (auto const& field : req_)
    res.push_back(std::pair<std::string, std::string>(field.name_string(),
                                                      field.value()));

  return res;
}

method_t BeastReq::get_method() {
  if (!is_from_req) return method_;

  std::string method(req_.method_string());

  if (methods_from.contains(method)) return methods_from[method];

  return UNDEFINED;
}

void BeastReq::set_body(const std::string& body) { body_ = body; }

void BeastReq::set_headers(const headers_t& headers) { headers_ = headers; }

void BeastReq::set_method(const method_t& method) { method_ = method; }

void BeastReq::set_target(const std::string& target) { target_ = target; }

ExtraData BeastReq::get_extra_data() { return extra_data_; }

void BeastReq::set_extra_data(const ExtraData& extra_data) {
  extra_data_ = extra_data;
}
