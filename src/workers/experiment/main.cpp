#include <time.h>
#include <chrono>
#include <memory>
#include "postgres_auth_repository.h"
#include "redis_auth_repository.h"
#include "yamlcpp_config.h"

#define ITERATIONS 1000
#define START 5000
#define END 1005001
#define STEP 100000
#define WORKER_ID 16

const std::string redis_section = "DB_AUTH_REDIS";
const std::string postgres_section = "DB_AUTH_POSTGRES";

class AuthRepositoriesTimeCompare {
 public:
  AuthRepositoriesTimeCompare(const std::shared_ptr<BaseAuthRepository>& rep1,
                              const std::shared_ptr<BaseAuthRepository>& rep2)
      : rep1_(rep1), rep2_(rep2) {}

  void compare(size_t min_rows, size_t max_rows, size_t step) {
    for (size_t i = 1; i < min_rows; i++) {
      rep1_->create_session(WORKER_ID, "test" + std::to_string(i));
      rep2_->create_session(WORKER_ID, "test" + std::to_string(i));
    }
    for (size_t i = min_rows; i < max_rows; i++) {
      rep1_->create_session(WORKER_ID, "test" + std::to_string(i));
      rep2_->create_session(WORKER_ID, "test" + std::to_string(i));
      if (i % step == 0) {
        size_t worker_id;
        std::cout << i << ",";
        auto start = std::chrono::system_clock::now();
        for (size_t j = 0; j < ITERATIONS; j++)
          rep1_->is_valid_session(worker_id, "test" + std::to_string(i));

        auto end = std::chrono::system_clock::now();
        std::cout << ""
                  << std::chrono::duration_cast<std::chrono::milliseconds>(
                         end - start)
                             .count() /
                         (double)ITERATIONS
                  << ",";

        start = std::chrono::system_clock::now();
        for (size_t j = 0; j < ITERATIONS; j++)
          rep2_->is_valid_session(worker_id, "test" + std::to_string(i));

        end = std::chrono::system_clock::now();
        std::cout << ""
                  << std::chrono::duration_cast<std::chrono::milliseconds>(
                         end - start)
                             .count() /
                         (double)ITERATIONS
                  << std::endl;
      }
    }
  }

 private:
  std::shared_ptr<BaseAuthRepository> rep1_;
  std::shared_ptr<BaseAuthRepository> rep2_;
};

int main(int argc, char* argv[]) {
  std::shared_ptr<BaseConfig> config(new YamlCppConfig(argv[1]));
  auto redis = std::shared_ptr<BaseAuthRepository>(
      new RedisAuthRepository(config, redis_section));

  auto postgres = std::shared_ptr<BaseAuthRepository>(
      new PostgresAuthRepository(config, postgres_section));

  AuthRepositoriesTimeCompare test(redis, postgres);
  test.compare(START, END, STEP);

  return 0;
}
