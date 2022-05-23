#ifndef REDISAUTHREPOSITORY_H
#define REDISAUTHREPOSITORY_H

#include <cstdlib>
#include <iostream>
#include <memory>
#include "base_auth_repository.h"
#include "base_config.h"

class RedisAuthRepository : public BaseAuthRepository {
 public:
  RedisAuthRepository(const std::shared_ptr<BaseConfig>& conf,
                      const std::string& connection_section);

  virtual void create_session(size_t worker_id,
                              const std::string& token) override;
  virtual bool is_valid_session(size_t& worker_id,
                                const std::string& token) override;

 private:
  std::shared_ptr<std::iostream> stream_;
};

#endif  // REDISAUTHREPOSITORY_H
