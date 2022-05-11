cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME "workers")

add_executable(${TARGET_NAME}
  main.cpp
  src/workers_handler.cpp
  src/workers_facade.cpp
  src/worker.cpp
  src/workers_controller.cpp
  src/commands.cpp
  src/workers_router.cpp
  src/postgres_workers_repository.cpp
  src/postgres_auth_repository.cpp
)

target_include_directories(${TARGET_NAME} PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/inc/
                           )

target_link_libraries(${TARGET_NAME}
    net_lib
    jsoncpp_lib
    pq
    pqxx)
