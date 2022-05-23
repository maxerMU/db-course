cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME "details")

add_executable(${TARGET_NAME}
  main.cpp
  src/details_handler.cpp
  src/producer.cpp
  src/detail.cpp
  src/details_facade.cpp
  src/swaps_controller.cpp
  src/commands.cpp
  src/details_router.cpp
  src/postgres_producers_repository.cpp
  src/postgres_details_repository.cpp
  src/postgres_swaps_repository.cpp
  src/postgres_stock_repository.cpp
)

target_include_directories(${TARGET_NAME} PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/inc/
                           )

target_link_libraries(${TARGET_NAME}
    net_lib
    jsoncpp_lib
    pq
    pqxx)

add_subdirectory(unit_tests)
