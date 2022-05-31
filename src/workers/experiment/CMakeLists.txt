cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME "workers_experiment")
set (REDISCPP_FLAGS "-DREDISCPP_HEADER_ONLY=ON")

add_executable(${TARGET_NAME}
  main.cpp
  ../src/postgres_auth_repository.cpp
  ../src/redis_auth_repository.cpp
)

target_include_directories(${TARGET_NAME} PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/../inc/
                           )

target_link_libraries(${TARGET_NAME}
    net_lib
    redis-cpp
    pq
    pqxx)
