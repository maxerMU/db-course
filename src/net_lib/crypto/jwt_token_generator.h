#ifndef JWTTOKENGENERATOR_H
#define JWTTOKENGENERATOR_H

#include "token_generator.h"
#include "base_config.h"
#include <memory>
#include <string>

class JWTTokenGenerator : public BaseTokenGenerator
{
public:
    JWTTokenGenerator(const std::shared_ptr<BaseConfig> &conf, std::string auth_section);
    virtual std::string generate_token() override;
    virtual bool check_expired(const std::string &token) override;

private:
    size_t minutes_to_expire_;
    std::string secret_word_;
};

#endif // JWTTOKENGENERATOR_H
