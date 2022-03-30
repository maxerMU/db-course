#include "beast_resp.h"

BeastResp::BeastResp(const http::response<http::string_body> &resp)
    : resp_(resp) {
  is_from_resp = true;
}

std::string BeastResp::get_body() const {
  if (is_from_resp)
    return resp_.body();

  return body_;
}

headers_t BeastResp::get_headers() const {
  if (!is_from_resp)
    return headers_;

  headers_t res;

  for (auto const &field : resp_)
    res.push_back(std::pair<std::string, std::string>(field.name_string(),
                                                      field.value()));

  return res;
}

int BeastResp::get_status() const {
  if (!is_from_resp)
    return status_;

  return resp_.result_int();
}

void BeastResp::set_body(const std::string &body) { body_ = body; }

void BeastResp::set_headers(const headers_t &headers) { headers_ = headers; }

void BeastResp::set_status(int status) { status_ = status; }

http::response<http::string_body>
make_beast_resp(const std::shared_ptr<Response> &resp) {
  http::response<http::string_body> res(http::status(resp->get_status()), 11);
  res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
  res.set(http::field::content_type, "text/html");
  // res.keep_alive(req_.keep_alive());
  res.body() = std::string{resp->get_body()};
  res.prepare_payload();

  return res;
}
