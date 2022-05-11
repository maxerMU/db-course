#ifndef TOKEN_GENERATOR_H
#define TOKEN_GENERATOR_H

#include <string>

class BaseTokenGenerator {
public:
    virtual std::string generate_token() = 0;
    virtual bool check_expired(const std::string &token) = 0;
};

#endif // TOKEN_GENERATOR_H
