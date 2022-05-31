cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME "details_da")

add_library(${TARGET_NAME}
  src/postgres_producers_repository.cpp
  src/postgres_details_repository.cpp
  src/postgres_swaps_repository.cpp
  src/postgres_stock_repository.cpp
)

target_include_directories(${TARGET_NAME} PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/inc/
                           ${CMAKE_CURRENT_SOURCE_DIR}/../bl/inc
                           )

target_link_libraries(${TARGET_NAME}
    net_lib
    pq
    pqxx)
