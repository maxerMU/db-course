#include "jwt_token_generator.h"
#include <chrono>
#include "base_sections.h"
#include "jwt/jwt.hpp"

JWTTokenGenerator::JWTTokenGenerator(const std::shared_ptr<BaseConfig>& conf,
                                     std::string auth_section)
    : minutes_to_expire_(conf->get_uint_field({auth_section, MinsExpSection})),
      secret_word_(conf->get_string_field({auth_section, SecretWordSection})) {}

std::string JWTTokenGenerator::generate_token() {
  jwt::jwt_object obj(jwt::params::algorithm("HS256"),
                      jwt::params::secret(secret_word_.c_str()));
  obj.add_claim("exp", std::chrono::system_clock::now() +
                           std::chrono::minutes{minutes_to_expire_});

  return obj.signature();
}

bool JWTTokenGenerator::check_expired(const std::string& token) {
  std::error_code ec;
  jwt::decode(token, jwt::params::algorithms({"HS256"}), ec,
              jwt::params::secret(secret_word_.c_str()),
              jwt::params::verify(true));
  return ec.value() == static_cast<int>(jwt::VerificationErrc::TokenExpired);
}
