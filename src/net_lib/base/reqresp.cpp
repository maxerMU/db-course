#include "reqresp.h"


std::string Response::get_body() const
{
    return body_;
}

headers_t Response::get_headers() const
{
    return headers_;
}

int Response::get_status() const {
    return status_;
}

void Response::set_body(const std::string &body)
{
    body_ = body;
}

void Response::set_headers(const headers_t &headers)
{
    headers_ = headers;
}

void Response::set_status(int status) {
    status_ = status;
}
