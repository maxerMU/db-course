#ifndef BEASTRESP_H
#define BEASTRESP_H

#include "net.h"
#include "reqresp.h"

class BeastResp : public Response {
public:
  BeastResp() = default;
  BeastResp(const http::response<http::string_body> &resp);
  std::string get_body() const override;
  void set_body(const std::string &body) override;

  headers_t get_headers() const override;
  void set_headers(const headers_t &headers) override;

  int get_status() const override;
  void set_status(int status) override;

private:
  std::string body_;
  headers_t headers_;
  int status_ = 200;

  http::response<http::string_body> resp_;

  bool is_from_resp = false;
};

http::response<http::string_body>
make_beast_resp(const std::shared_ptr<Response> &resp);

#endif // BEASTRESP_H
