#include "redis_auth_repository.h"
#include <redis-cpp/execute.h>
#include <redis-cpp/stream.h>
#include "base_sections.h"
#include "database_exceptions.h"

RedisAuthRepository::RedisAuthRepository(
    const std::shared_ptr<BaseConfig>& conf,
    const std::string& connection_section) {
  auto host = conf->get_string_field({connection_section, DbHostSection});
  auto port = conf->get_uint_field({connection_section, DbPortSection});
  stream_ = rediscpp::make_stream(host, std::to_string(port));
}

void RedisAuthRepository::create_session(size_t worker_id,
                                         const std::string& token) {
  auto resp = rediscpp::execute(*stream_, "set", token.c_str(),
                                std::to_string(worker_id).c_str());

  if (resp.empty())
    throw DatabaseExecutionException("can't add session to redis");
}

bool RedisAuthRepository::is_valid_session(size_t& worker_id,
                                           const std::string& token) {
  auto resp = rediscpp::execute(*stream_, "get", token.c_str());
  if (resp.empty())
    return false;

  worker_id = std::stoull(resp.as<std::string>());
  return true;
}
